#include "../include/idt.h"

idt_entry_t idt[256];
idt_ptr_t idtp;

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].isr_low = (base & 0xFFFF);
    idt[num].isr_high = (base >> 16) & 0xFFFF;
    idt[num].kernel_cs = sel;
    idt[num].reserved = 0;
    
    //we must uncomment the OR operation below once we set up the GDT, 
    // but for now, we just set the exact flags (usually 0x8E for 32-bit interrupts)
    idt[num].attributes = flags /* | 0x60 */; 
}

void init_idt() {
    idtp.limit = (sizeof(idt_entry_t) * 256) - 1;
    idtp.base = (uint32_t)&idt;
    for (int i = 0; i < 256; i++) {
        idt_set_gate(i, 0, 0, 0);
    }
    __asm__ volatile ("lidt %0" : : "m" (idtp));
}