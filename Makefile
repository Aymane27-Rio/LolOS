CC = gcc
AS = nasm
LD = ld

CFLAGS = -m32 -ffreestanding -c
LDFLAGS = -m elf_i386 -T linker.ld

all: myos.bin

myos.bin: boot/boot.o kernel/kernel.o
	$(LD) $(LDFLAGS) boot/boot.o kernel/kernel.o -o myos.bin

boot/%.o: boot/%.s
	$(AS) -f elf32 $< -o $@

kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f boot/*.o kernel/*.o *.bin

run: myos.bin
	qemu-system-i386 -kernel myos.bin -display curses