#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/tty.h>

void kmain(void) {
  gdt_init();
  idt_init();
  term_init();
  term_writestr("[+] gdt loaded successfully\n");
  term_writestr("[+] idt loaded successfully\n");
  term_writestr("[i] Welcome to the CatOS v0.0\n");
  for (;;);
}
