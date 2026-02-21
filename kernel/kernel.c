#include <stdint.h>
#include "../include/io.h"

char get_keypress();

// this will be the global terminal state for the cursor position and VGA buffer pointer
int cursor_x = 0;
int cursor_y = 0;
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;

// the cursor stuff
void update_cursor(int x, int y) {
    uint16_t pos = y * 80 + x; // 80 columns per row (i think this will be changed later when we add scrolling)
    
    // the low byte of the cursor position (register 0x0F)
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    
    // the high byte of the cursor position (register 0x0E)
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

// the special characters handling
void print_char(char c) {
    if (c == '\n') { // "Enter" key
        cursor_x = 0;
        cursor_y++;
    } else if (c == '\b') { // "Backspace" key
        if (cursor_x > 0) {
            cursor_x--;
            vga_buffer[cursor_y * 80 + cursor_x] = (uint16_t)' ' | (uint16_t)0x0F00;
        }
    } else { // normal characters handling
        vga_buffer[cursor_y * 80 + cursor_x] = (uint16_t)c | (uint16_t)0x0F00;
        cursor_x++;
    }
    // handle line wrapping when we reach the end of a line
    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
    }
    
    // preventing off-screen writing (this is just a temporary fix until i add scrolling)
    if (cursor_y >= 25) {
        cursor_y = 0;
    }
    update_cursor(cursor_x, cursor_y);
}
//function to print full strings much easily
void print_string(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        print_char(str[i]);
    }
}
//custom string comparison function (since i don't have the standard library, je pleugh)
int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

void kmain() {
    for(int i = 0; i < 2000; i++) {
        vga_buffer[i] = (uint16_t)' ' | (uint16_t)0x0F00;
    }

    //the moment of truth
    print_string("Welcome to Lol OS v0.1!\n");
    char command_buffer[256];
    int buffer_index = 0;
    // input loop
    while (1) {
        char key = get_keypress();
        if (key !=0){
            if (key == '\n') {
                print_char('\n');
                command_buffer[buffer_index] = '\0'; 
            
                if (buffer_index > 0){
                    if (strcmp(command_buffer, "help")==0){
                        print_string("Available commands: help, clear\n");
                        } 
                        else if (strcmp(command_buffer, "clear") == 0) {
                            for(int i = 0; i < 2000; i++) {
                                vga_buffer[i] = (uint16_t)' ' | (uint16_t)0x0F00;
                            }
                            cursor_x = 0;
                            cursor_y = 0;
                            update_cursor(0, 0);
                        } 
                        else {
                            print_string("Unknown command: ");
                            print_string(command_buffer);
                            print_char('\n');
                        }
                    }
                    // don't wanna deal with memory mgmt
                    buffer_index = 0;
                    print_string("> ");
                } 
                // backspace
                else if (key == '\b') {
                    if (buffer_index > 0) {
                        buffer_index--;     
                        print_char('\b'); 
                    }
                } 
                // normal characters, unlike me
                else {
                    if (buffer_index < 254) {
                        command_buffer[buffer_index] = key;
                        buffer_index++;
                        print_char(key);
                    }
                }
            }
        }      }