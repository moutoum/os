// File: tty.c
// File Created: 12 Apr 2019 16:00
// By Maxence Moutoussamy <maxence.moutoussamy1@gmail.com>

#include <stddef.h>
#include <stdint.h>

#include "vga.h"

#define KERNEL_TTY_WIDTH 80
#define KERNEL_TTY_HEIGHT 25

static uint16_t *const kernel_tty_memory = (uint16_t *)0xB8000;
static size_t kernel_tty_row = 0;
static size_t kernel_tty_col = 0;
static uint8_t kernel_tty_color = 0;

static void __kernel_tty_write_cell(size_t idx, char c, uint8_t color) {
    kernel_tty_memory[idx] = (uint16_t)c | (uint16_t)color << 8;
}

// kernel_tty_color_set sets the color of the tty for the next prints.
void kernel_tty_color_set(vga_color_t fg, vga_color_t bg) {
    kernel_tty_color = fg | bg << 4;
}

// kernel_tty_clear clears the buffer with spaces and the vga_color global
// variable.
void kernel_tty_clear() {
    size_t i = 0;
    while (i < KERNEL_TTY_WIDTH * KERNEL_TTY_HEIGHT) {
        __kernel_tty_write_cell(i, ' ', kernel_tty_color);
        i++;
    }
}

// kernel_tty_initialize initializes the buffer and the internal variables.
void kernel_tty_initialize(void) {
    kernel_tty_col = 0;
    kernel_tty_row = 0;
    kernel_tty_color_set(VGA_COLOR_BLACK, VGA_COLOR_WHITE);
    kernel_tty_clear();
}

// kernel_tty_putc prints the given char to the tty.
void kernel_tty_putc(char c) {
    if (c == '\n') {
        kernel_tty_row = 0;
        kernel_tty_col++;
        return;
    }

    if (c == '\r') {
        kernel_tty_row = 0;
        return;
    }

    if (c == '\b') {
        if (kernel_tty_row > 0) {
            kernel_tty_row--;
        }
        return;
    }

    const size_t idx = kernel_tty_col * KERNEL_TTY_WIDTH + kernel_tty_row;
    __kernel_tty_write_cell(idx, c, kernel_tty_color);

    if (kernel_tty_row == KERNEL_TTY_WIDTH) {
        kernel_tty_col++;
        kernel_tty_row = 0;
    } else {
        kernel_tty_row++;
    }
}

// kernel_tty_write prints the bytes contained in data.
void kernel_tty_write(const void *data, size_t size) {
    size_t i = 0;

    while (i < size) {
        kernel_tty_putc(((char *)data)[i]);
        i++;
    }
}

// kernel_tty_puts prints the string that ends with a null byte ('\0').
void kernel_tty_puts(const char *s) {
    while (*s) kernel_tty_putc(*s), s++;
    kernel_tty_putc('\n');
}
