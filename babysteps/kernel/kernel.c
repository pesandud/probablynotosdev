#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum vga_color {
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_LIGHT_BROWN = 14,
  VGA_COLOR_WHITE = 15
} vga_color_t;

typedef uint8_t u8;
typedef uint16_t u16;
typedef unsigned char uchar;

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

size_t term_row, term_col;
u8 term_clr;
u16* term_buf = (u16*)VGA_MEMORY;

static inline u8 vga_entry_clr(vga_color_t fg, vga_color_t bg) {
  return fg | bg << 4;
}

static inline u16 vga_entry(uchar c, u8 color) {
  return (u16)c | (u16)color << 8;
}

size_t strlen(const char* s) {
  size_t len = 0;
  while (s[len]) len++;
  return len;
}

void term_init(void) {
  term_row = 0;
  term_col = 0;
  term_clr = vga_entry_clr(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t idx = y * VGA_WIDTH + x;
      term_buf[idx] = vga_entry(' ', term_clr);
    }
  }
}

void term_setclr(u8 clr) { term_clr = clr; }

void term_putentryat(uchar c, u8 clr, size_t x, size_t y) {
  const size_t idx = y * VGA_WIDTH + x;
  term_buf[idx] = vga_entry(c, clr);
}

void term_putchar(uchar c) {
  if (c == '\n') {
    term_col = 0;
    if (++term_row >= VGA_HEIGHT) term_row = 0;
    return;
  }

  term_putentryat(c, term_clr, term_col, term_row);

  if (++term_col >= VGA_WIDTH) {
    term_col = 0;
    if (++term_row >= VGA_HEIGHT) {
      term_row = 0;
    }
  }
}

void term_write(const char* s, size_t size) {
  for (size_t i = 0; i < size; i++) {
    term_putchar(s[i]);
  }
}

void term_writestr(const char* s) { term_write(s, strlen(s)); }

void kernel_main(void) {
  term_init();
  term_writestr("LOL IM NOOB THO :D\n");
}
