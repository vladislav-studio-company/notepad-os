# Notepad OS Makefile
# Builds a 32-bit multiboot kernel and a bootable ISO

CC      = gcc
AS      = nasm
LD      = ld

CFLAGS  = -m32 -ffreestanding -O2 -Wall -Wextra -fno-pic -fno-stack-protector -fno-builtin
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld

KERNEL  = kernel.elf
ISO     = notepad-os.iso

all: $(KERNEL)

boot.o: boot.asm
	$(AS) $(ASFLAGS) boot.asm -o boot.o

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o

$(KERNEL): boot.o kernel.o linker.ld
	$(LD) $(LDFLAGS) -o $(KERNEL) boot.o kernel.o

iso: $(KERNEL)
	mkdir -p isodir/boot/grub
	cp $(KERNEL) isodir/boot/kernel.elf
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) isodir

run: iso
	qemu-system-i386 -cdrom $(ISO)

clean:
	rm -f *.o $(KERNEL) $(ISO)
	rm -rf isodir

.PHONY: all iso run clean
