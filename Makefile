CC = gcc

CFLAGS = -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Werror
LDFLAGS = -m elf_i386 -T linker.ld
AS = nasm
ASFLAGS = -f elf32

OBJS = boot/boot.o kernel/kernel.o kernel/keyboard.o kernel/terminal.o kernel/string.o kernel/cmos.o kernel/shell.o kernel/cpu.o

all: myos.bin

myos.bin: $(OBJS)
		ld $(LDFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

run: myos.bin
	qemu-system-i386 -kernel myos.bin

clean:
	rm -f $(OBJS) myos.bin