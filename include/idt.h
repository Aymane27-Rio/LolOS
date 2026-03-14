#ifndef IDT_H
#define IDT_H
#include <stdint.h>

typedef struct {
    uint16_t isr_low;      // the lower 16 bits of the ISR's address
    uint16_t kernel_cs;    // the GDT segment selector that the CPU will load
    uint8_t  reserved;     // set to zero
    uint8_t  attributes;   // type and attributes (e.g., 0x8E for an Interrupt Gate)
    uint16_t isr_high;     // the higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void init_idt();

#endif