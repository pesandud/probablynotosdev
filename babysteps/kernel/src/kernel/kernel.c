#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <kernel/tty.h>

void kmain(void) {
  gdt_init();
  idt_init();
	pic_init(IRQ_BASE, IRQ_BASE + 8);

	// unmask the keyboard irq
	pic_unmask(1);

	__asm__ volatile ("sti");

  term_init();

  term_writestr("[+] gdt loaded\n");
  term_writestr("[+] idt loaded\n");
  term_writestr("[+] interrupts live\n");
  term_writestr("[i] Welcome to the CatOS v0.0\n");
  for (;;);
}
