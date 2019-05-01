# File: Makefile
# File Created: 09 Apr 2019 10:58
# By Maxence Moutoussamy <maxence.moutoussamy1@gmail.com>

LINKER_CFG_FILE = linker.ld

CC = i686-elf-gcc
CASM = nasm

CFLAGS = \
	-std=gnu99 \
	-ffreestanding \
	-O2 \
	-Wall \
	-Wextra \
	-I ./include

ASMFLAGS = \
	-f elf32

CSOURCES = \
	src/kernel.c \
	src/tty.c

ASMSOURCES = \
	src/boot.S

OBJS = $(CSOURCES:.c=.o) $(ASMSOURCES:.S=.o)

os.iso: kernel grub.cfg
	mkdir -p iso/boot/grub
	cp kernel iso/boot/kernel
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o $@ iso

kernel: $(LINKER_CFG_FILE) $(OBJS)
	echo $(OBJS)
	i686-elf-gcc -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $(OBJS) -lgcc

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CASM) $(ASMFLAGS) $< -o $@

.PHONY: run
run: os.iso
	qemu-system-i386 -cdrom os.iso

.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -rf iso

.PHONY: fclean
fclean: clean
	rm -f kernel
	rm -f os.iso