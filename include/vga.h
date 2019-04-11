// File: vga.h
// File Created: 11 Apr 2019 16:17
// By Maxence Moutoussamy <maxence.moutoussamy1@gmail.com>

#if !defined(__VGA_H__)
#define __VGA_H__

#include <stdint.h>

#define LIGHTER(color) (color + 0x8)

typedef enum vga_color {
    // Normal colors
    VGA_COLOR_BLACK = 0x0,
    VGA_COLOR_BLUE = 0x1,
    VGA_COLOR_GREEN = 0x2,
    VGA_COLOR_CYAN = 0x3,
    VGA_COLOR_RED = 0x4,
    VGA_COLOR_MAGENTA = 0x5,
    VGA_COLOR_BROWN = 0x6,
    VGA_COLOR_LIGHT_GRAY = 0x7,

    // Light colors
    VGA_COLOR_DARK_GRAY = LIGHTER(VGA_COLOR_BLACK),
    VGA_COLOR_LIGHT_BLUE = LIGHTER(VGA_COLOR_BLUE),
    VGA_COLOR_LIGHT_GREEN = LIGHTER(VGA_COLOR_GREEN),
    VGA_COLOR_LIGHT_CYAN = LIGHTER(VGA_COLOR_CYAN),
    VGA_COLOR_LIGHT_RED = LIGHTER(VGA_COLOR_RED),
    VGA_COLOR_LIGHT_MAGENTA = LIGHTER(VGA_COLOR_MAGENTA),
    VGA_COLOR_YELLOW = LIGHTER(VGA_COLOR_BROWN),
    VGA_COLOR_WHITE = LIGHTER(VGA_COLOR_LIGHT_GRAY),
} vga_color_t;

void vga_initialize(void);
void vga_color_set(uint8_t color);
void vga_put_c(char c);
void vga_put_str(const char *s);
uint8_t vga_term_color(vga_color_t foreground, vga_color_t background);

#endif // __VGA_H__
