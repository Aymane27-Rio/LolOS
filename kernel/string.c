#include "../include/string.h"

int strcmp(const char* s1, const char* s2) { // ewa shghadyr mazal ma endna standard library
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

char* strcpy(char* dest, const char* src) {
    char* original_dest = dest;
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; // matnsash, null-terminate the new string!
    return original_dest;
}

// memset fills a block of memory with a specific value. 
// i heard this is used to quickly zero-out memory
void* memset(void* ptr, int value, size_t num) {
    unsigned char* p = (unsigned char*)ptr;
    for (size_t i = 0; i < num; i++) {
        p[i] = (unsigned char)value;
    }
    return ptr;
}

//memsetw fills a block of memory with a specific 16-bit value. i heard it's perfect for clearing VGA text buffers

uint16_t* memsetw(uint16_t* dest, uint16_t val, size_t count) {
    uint16_t* temp = (uint16_t*)dest;
    for(size_t i = 0; i < count; i++) {
        *temp++ = val;
    }
    return dest;
}