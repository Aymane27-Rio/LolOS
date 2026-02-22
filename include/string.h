#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>

// for strings
int strcmp(const char* s1, const char* s2);
size_t strlen(const char* str);
char* strcpy(char* dest, const char* src);

// for memory (ew)
void* memset(void* ptr, int value, size_t num);
uint16_t* memsetw(uint16_t* dest, uint16_t val, size_t count);
int atoi(const char* str);

#endif