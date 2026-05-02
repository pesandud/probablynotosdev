#include <kernel/pic.h>
#include <stdint.h>

static inline void outb(uint16_t port, uint8_t val) {
  __asm__ volatile("outb %b0, %w1" ::"a"(val), "Nd"(port) : "memory");
}

static inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  __asm__ volatile("inb %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory");
  return ret;
}

static inline void io_wait(void) {
  // burn some cpu cycles
  outb(0x80, 0);
}

void pic_send_eoi(uint8_t irq) {
  if (irq >= 8)
    outb(PIC2_COMMAND, PIC_EOI);
  outb(PIC1_COMMAND, PIC_EOI);
}

/*
 * offset1: vector offset for master pic
 * offset2: vector offset for slave pic
 */
void pic_init(int offset1, int offset2) {
	// restore the current interrupt masks
	unsigned char a1, a2;
	a1 = inb(PIC1_DATA);
	a2 = inb(PIC2_DATA);

	// start initialization in cascade mode
  outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
  io_wait();
  outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
  io_wait();

  // ICW2
  // master pic vector offset
  outb(PIC1_DATA, offset1);
  io_wait();
  // slave pic vector offset
  outb(PIC2_DATA, offset2);
  io_wait();

  // ICW3
  // tell master pic that we have a slave pic at irq2
  outb(PIC1_DATA, 1 << CASCADE_IRQ);
  io_wait();
  // tell slave pic their id
  outb(PIC2_DATA, 2);
  io_wait();

  // tell pics to use 8086 mode
  outb(PIC1_DATA, ICW4_8086);
  io_wait();
  outb(PIC2_DATA, ICW4_8086);
  io_wait();

  // unmask both pics
  outb(PIC1_DATA, a1);
  outb(PIC2_DATA, a2);
}

void pic_mask(uint8_t irq_line) {
  uint16_t port;
  uint8_t value;

  port = (irq_line < 8) ? PIC1_DATA : PIC2_DATA;
  if (irq_line >= 8)
    irq_line -= 8;

  value = inb(port) | (1 << irq_line);
  outb(port, value);
}

void pic_unmask(uint8_t irq_line) {
  uint16_t port;
  uint8_t value;

  port = (irq_line < 8) ? PIC1_DATA : PIC2_DATA;
  if (irq_line >= 8)
    irq_line -= 8;

  value = inb(port) & ~(1 << irq_line);
  outb(port, value);
}
