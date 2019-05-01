// File: kernel_main.c
// File Created: 11 Apr 2019 14:27
// By Maxence Moutoussamy <maxence.moutoussamy1@gmail.com>

#include <stdint.h>
#include <stddef.h>
#include "tty.h"

size_t strlen(const char *s) {
    size_t i = 0;
    while (*s) i++, s++;
    return (i);
}

void kernel_main(void) { 
    kernel_tty_initialize();
    kernel_tty_puts("Hello, world!");
    kernel_tty_puts("Welcome on my operating system.");
    kernel_tty_color_set(VGA_COLOR_LIGHT_RED, VGA_COLOR_WHITE);
    kernel_tty_puts("Sorry but you can't do anything for the moment...");
}