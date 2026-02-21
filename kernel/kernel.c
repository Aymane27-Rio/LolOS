#include <stdint.h>

void kmain() {
    // Point directly to the VGA hardware text buffer
    volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
    
    const char* str = "Hello LolOS!";
    int index = 0;

    // Loop through the string
    while (str[index] != '\0') {
        vga_buffer[index] = (uint16_t)str[index] | (uint16_t)0x0F00;
        index++;
    }
}