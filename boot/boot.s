MBALIGN  equ  1 << 0
MEMINFO  equ  1 << 1
FLAGS    equ  MBALIGN | MEMINFO
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .bss
align 16
stack_bottom:
    resb 16384 ; Reserve 16 Kilobytes of memory for our stack
stack_top:

section .text
global _start
extern kmain

_start:
    cli             ; disable interrupts
    mov esp, stack_top ; set the cpu's stack pointer to the new memory
    call kmain      ; jump to the C code
    hlt             ; halt the CPU if the C code finishes