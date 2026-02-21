#include <stdint.h>
#include "../include/io.h"
#include "../include/terminal.h"
#include "../include/string.h"

int cursor_x = 0;
int cursor_y = 0;
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;

uint8_t terminal_color = 0x0F;

void update_cursor(int x, int y) {
    uint16_t pos = y * 80 + x; 
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}
// hacker theme, lol
void terminal_apply_theme(uint8_t color){
    terminal_color = color;
    for (int i = 0; i < 2000; i++){
        uint16_t character = vga_buffer[i] & 0x00FF;
        vga_buffer[i] = character | (terminal_color << 8);
    }
}

void scroll() {
    for (int y = 0; y < 24; y++) {
        for (int x = 0; x < 80; x++) {
            vga_buffer[y * 80 + x] = vga_buffer[(y + 1) * 80 + x];
        }
    }
    uint16_t blank = (uint16_t)' ' | (uint16_t)terminal_color << 8;
    memsetw((uint16_t*)(vga_buffer + 24 * 80), blank, 80);
    cursor_y = 24;
}

void terminal_clear() {
    uint16_t blank = (uint16_t)' ' | (uint16_t)terminal_color << 8;
    memsetw((uint16_t*)vga_buffer, blank, 2000);
    cursor_x = 0;
    cursor_y = 0;
    update_cursor(0, 0);
}

void terminal_init() {
    terminal_clear();
    const char* logo =
    " _          _  ___      \n"
    "| |    ___ | |/ _ \\ ___ \n"
    "| |   / _ \\| | | | / __|\n"
    "| |__| (_) | | |_| \\__ \\\n"
    "|_____\\___/|_|\\___/|___/\n"
    "                CLI v0.3\n\n> ";

    print_string(logo);
}

void print_char(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c == '\b') {
        if (cursor_x > 0) {
            cursor_x--;
            vga_buffer[cursor_y * 80 + cursor_x] = (uint16_t)' ' | (uint16_t)terminal_color << 8;
        }
    } else {
        vga_buffer[cursor_y * 80 + cursor_x] = (uint16_t)c | (uint16_t)terminal_color << 8;
        cursor_x++;
    }

    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
    }
    if (cursor_y >= 25) {
        scroll();
    }
    update_cursor(cursor_x, cursor_y);
}

void print_string(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        print_char(str[i]);
    }
}

void print_time_number(int num) {
    if (num < 10) {
        print_char('0'); 
    }
    if (num >= 10) {
        print_char((num / 10) + '0'); 
    }
    print_char((num % 10) + '0');
}