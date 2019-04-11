// File: kernel_main.c
// File Created: 11 Apr 2019 14:27
// By Maxence Moutoussamy <maxence.moutoussamy1@gmail.com>

#include <stdint.h>
#include <stddef.h>
#include "vga.h"

size_t strlen(const char *s) {
    size_t i = 0;
    while (*s) i++, s++;
    return (i);
}

void kernel_main(void) { 
    vga_initialize();
    vga_put_str("Hello, world!\n");
    vga_put_str("Welcome on my operating system.\n");
    vga_color_set(vga_term_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_WHITE));
    vga_put_str("Sorry but you can't do anything for the moment...");
}