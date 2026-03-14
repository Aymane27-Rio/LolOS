#include "../include/io.h"

int shift_pressed = 0;
// US QWERTY layout map to convert PS/2 scancodes to ASCII characters
const char kbd_us[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',   
    0,  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   
    0,  '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,
  '*',  0,  ' ',  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,  0,  0,  '-',  0,  0,  0,  '+',  0,  0,  0,   0,   0,   0,   0,   0,
    0,  0,  0,   0,   0,  0,  0,   0,   0,  0,  0,   0,   0,   0,   0,   0
};

const char kbd_us_shift[128] = {
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',   
  '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',   
    0,  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',   
    0,  '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',   0,
  '*',  0,  ' ',  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,  0,  0,  '-',  0,  0,  0,  '+',  0,  0,  0,   0,   0,   0,   0,   0,
    0,  0,  0,   0,   0,  0,  0,   0,   0,  0,  0,   0,   0,   0,   0,   0
};


char get_keypress() {
    uint8_t status = inb(0x64);
    if (status & 1) {
        if (status & 0x20) {
            // inb(0x60); // read it just to clear the hardware buffer
            return 0;  // do not type anything, please
        }
        uint8_t scancode = inb(0x60);
        if (scancode == 0x2A || scancode == 0x36) { 
            shift_pressed = 1; 
            return 0; 
        }
        if (scancode == 0xAA || scancode == 0xB6) { 
            shift_pressed = 0; 
            return 0; 
        }
        if (scancode & 0x80) return 0;
        if (scancode < 128) {
            if (shift_pressed) {
                return kbd_us_shift[scancode];
            } else {
                return kbd_us[scancode];
            }
        }
    }
    return 0;
    
}