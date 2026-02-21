#include "../include/io.h"

// US QWERTY layout map to convert PS/2 scancodes to ASCII characters
const char kbd_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',       
    0,  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   0,       
  '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0, '*', 0, ' '
};

uint8_t last_scancode = 0;

char get_keypress() {
    // letting the hardware know we want to read the keyboard data
    while ((inb(0x64) & 1) == 0); 
    uint8_t scancode = inb(0x60);
    
    // omiting duplicate signals to prevent the repeating glitch that i noticed when holding down a key
    if (scancode == last_scancode) {
        return 0;
    }
    last_scancode = scancode;

    // only return valid key-down events and ignore key releases/unknowns
    if (scancode < 128) {
        return kbd_map[scancode];
    }
    return 0; 
}