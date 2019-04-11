; File: Makefile
; File Created: 09 Apr 2019 10:58
; By Maxence Moutoussamy <maxence.moutoussamy1@gmail.com>

; starting symbol
global _start

; Multiboot initialisation
MAGIC equ 0x1BADB002
FLAGS equ 0
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

; kernel stack allocation
KSTACK_SIZE equ 16384
section .bss
align 16
kstack_bottom:
	resb KSTACK_SIZE
kstack_top:

; starting kernel
section .text
_start:
	mov esp, kstack_top
	mov eax, 0xDEADBEEF ; Just here to verify the initialisation manually -> To remove later
	extern kernel_main
	call kernel_main

; kernel finished
.loop:	
	jmp .loop