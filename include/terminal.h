#ifndef TERMINAL_H
#define TERMINAL_H
#include <stdint.h>

void terminal_init();
void terminal_clear();
void print_char(char c);
void print_string(const char* str);
void terminal_apply_theme(uint8_t color);
void print_time_number(int num);
#endif