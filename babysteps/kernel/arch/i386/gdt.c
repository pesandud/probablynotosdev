#include <kernel/gdt.h>

#define GDT_ENTRIES 3

static gdt_entry_t gdt[GDT_ENTRIES];
static gdtr_t gdtr;

extern void gdt_flush(uint32_t);

static void set_gdt(int i, uint32_t base, uint32_t limit, uint8_t access,
                    uint8_t gran) {
  gdt[i].base_low = base & 0xffff;
  gdt[i].base_mid = (base >> 16) & 0xff;
  gdt[i].base_high = (base >> 24) & 0xff;
  gdt[i].limit_low = limit & 0xffff;
  gdt[i].granularity = ((limit >> 16) & 0xf) | (gran & 0xf0);
  gdt[i].access = access;
}

void gdt_init(void) {
  gdtr.limit = sizeof(gdt) - 1;
  gdtr.base = (uint32_t)&gdt;

  set_gdt(0, 0, 0, 0, 0);
  // kernel code n data
  set_gdt(1, 0, 0xffffffff, 0x9a, 0xcf);
  set_gdt(2, 0, 0xffffffff, 0x92, 0xcf);
  // user code n data
  set_gdt(3, 0, 0xffffffff, 0xfa, 0xcf);
  set_gdt(4, 0, 0xffffffff, 0xf2, 0xcf);

  gdt_flush((uint32_t)&gdtr);
}
