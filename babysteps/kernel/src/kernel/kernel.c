#include <kernel/tty.h>
#include <kernel/gdt.h>

void kmain(void) {
  gdt_init();
  term_init();
	term_writestr("[+] gdt loaded successfully\n");
	term_writestr("welcome to the pesanduOS v0.0\n");
  for (;;);
}
