// File: tty.h
// File Created: 12 Apr 2019 16:29
// By Maxence Moutoussamy <maxence.moutoussamy1@gmail.com>

#if !defined(__KERNEL_TTY_H__)
#define __KERNEL_TTY_H__

#include <stddef.h>
#include "vga.h"

// kernel_tty_initialize initializes the buffer and the internal variables.
void kernel_tty_initialize(void);

// kernel_tty_clear clears the buffer with spaces and the vga_color global
// variable.
void kernel_tty_clear();

// kernel_tty_putc prints the given char to the tty.
void kernel_tty_putc(char c);

// kernel_tty_write prints the bytes contained in data.
void kernel_tty_write(const void *data, size_t size);

// kernel_tty_color_set sets the color of the tty for the next prints.
void kernel_tty_color_set(vga_color_t fg, vga_color_t bg);

// kernel_tty_puts prints the string that ends with a null byte ('\0').
void kernel_tty_puts(const char *s);

#endif  // __KERNEL_TTY_H__
