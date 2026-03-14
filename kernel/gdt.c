#include "../include/gdt.h"

uint64_t gdt[3];

//the pointer structure the CPU requires
struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdtp;

void init_gdt() {
    gdt[0] = 0; 
    gdt[1] = 0x00CF9A000000FFFF;
    gdt[2] = 0x00CF92000000FFFF;
    gdtp.limit = sizeof(gdt) - 1;
    gdtp.base = (uint32_t)&gdt;

    // load the GDT, then perform a "Far Jump" to flush the CPU pipeline
    // and force it to use our brand new Code Segment (0x08)
    __asm__ volatile (
        "lgdt %0\n\t"
        "pushl $0x08\n\t"
        "pushl $1f\n\t"
        "retf\n\t"
        "1:\n\t"
        "mov $0x10, %%ax\n\t"
        "mov %%ax, %%ds\n\t"
        "mov %%ax, %%es\n\t"
        "mov %%ax, %%fs\n\t"
        "mov %%ax, %%gs\n\t"
        "mov %%ax, %%ss\n\t"
        : : "m" (gdtp) : "eax", "memory"
    );
}