# File: Makefile
# File Created: 09 Apr 2019 10:58
# By Maxence Moutoussamy <maxence.moutoussamy1@gmail.com>

os.iso: kernel grub.cfg
	mkdir -p iso/boot/grub
	cp kernel iso/boot/kernel
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o $@ iso

kernel: src/boot.o src/linker.ld src/kernel.o
	i686-elf-gcc -T src/linker.ld -o $@ -ffreestanding -O2 -nostdlib src/boot.o src/kernel.o -lgcc

src/boot.o: src/boot.s
	nasm -f elf32 $< -o $@

src/kernel.o: src/kernel.c
	i686-elf-gcc -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

.PHONY: run
run: os.iso
	qemu-system-i386 -cdrom os.iso

.PHONY: clean
clean:
	rm -f src/boot.o
	rm -f src/kernel.o
	rm -rf iso

.PHONY: fclean
fclean: clean
	rm -f kernel
	rm -f os.iso