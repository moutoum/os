// File: vga.c
// File Created: 11 Apr 2019 16:15
// By Maxence Moutoussamy <maxence.moutoussamy1@gmail.com>

#include <stddef.h>

#include "vga.h"

#define VGA_BUFFER_ADDRESS 0xB8000
#define VGA_TERM_WIDTH 80
#define VGA_TERM_HEIGHT 25
#define VGA_TERM_INDEX(x, y) ((y * VGA_TERM_WIDTH) + x)

static uint8_t vga_column_cursor;
static uint8_t vga_row_cursor;
static uint8_t vga_color;
static uint16_t *vga_buffer;

/*
    vga_term_color creates a color from a foreground and a background color.
*/
uint8_t vga_term_color(vga_color_t foreground, vga_color_t background) {
    return (foreground | background << 4);
}

/*
    vga_term_cell creates a vga cell from a character and a color.
*/
static inline uint16_t vga_term_cell(unsigned char c, uint8_t color) {
    return ((uint16_t)c | (uint16_t)color << 8);
}

/*
    vga_clear clears the buffer with spaces and the vga_color global variable.
*/
void vga_clear() {
    const char clear_char = ' ';
    const size_t max_index = VGA_TERM_WIDTH * VGA_TERM_HEIGHT;
    size_t i = 0;

    while (i < max_index) {
        vga_buffer[i] = vga_term_cell(clear_char, vga_color);
        i++;
    }
}

/*
    vga_initilize initializes the vga buffer and the internal variables.
*/
void vga_initialize(void) {
    vga_column_cursor = 0;
    vga_row_cursor = 0;
    vga_color = vga_term_color(VGA_COLOR_BLACK, VGA_COLOR_WHITE);
    vga_buffer = (uint16_t *)VGA_BUFFER_ADDRESS;
    vga_clear();
}

/*
    vga_color_set places the color given as color for next prints.
*/
void vga_color_set(uint8_t color) { vga_color = color; }

/*
    vga_put_c prints the given character and increase the cursors.
*/
void vga_put_c(char c) {
    if (c == '\n') {
        vga_row_cursor = 0;
        vga_column_cursor++;
        return;
    }

    if (c == '\r') {
        vga_row_cursor = 0;
        return;
    }

    if (c == '\b') {
        if (vga_row_cursor > 0) {
            vga_row_cursor--;
        }
        return;
    }

    vga_buffer[VGA_TERM_INDEX(vga_row_cursor, vga_column_cursor)] =
        vga_term_cell(c, vga_color);

    if (vga_row_cursor == VGA_TERM_WIDTH) {
        vga_column_cursor++;
        vga_row_cursor = 0;
    } else {
        vga_row_cursor++;
    }
}

// vga_put_str prints a null terminated ('\0') string.
void vga_put_str(const char *s) {
    while (*s) {
        vga_put_c(*s);
        s++;
    }
}