#include "../include/timer.h"
#include "../include/io.h"

uint32_t timer_ticks = 0;

void timer_handler() {
    timer_ticks++;
    outb(0x20, 0x20); 
}