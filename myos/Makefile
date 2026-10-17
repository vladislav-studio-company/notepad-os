# Makefile для Notepad OS Lite

CC      = gcc
AS      = nasm
LD      = ld

CFLAGS  = -m32 -ffreestanding -O2 -Wall -Wextra -fno-pic -fno-stack-protector
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld

all: kernel.elf

boot.o: boot.asm
	$(AS) $(ASFLAGS) boot.asm -o boot.o

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o

kernel.elf: boot.o kernel.o linker.ld
	$(LD) $(LDFLAGS) -o kernel.elf boot.o kernel.o

iso: kernel.elf grub.cfg
	mkdir -p isodir/boot/grub
	cp kernel.elf isodir/boot/kernel.elf
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o notepad-os.iso isodir

run: iso
	qemu-system-i386 -cdrom notepad-os.iso

clean:
	rm -f *.o kernel.elf notepad-os.iso
	rm -rf isodir

.PHONY: all iso run clean
