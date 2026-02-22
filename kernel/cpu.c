#include "../include/cpu.h"
#include <stdint.h>

void get_cpu_vendor(char* vendor) {
    uint32_t ebx, ecx, edx;

    __asm__ volatile (
        "cpuid"
        : "=b" (ebx), "=c" (ecx), "=d" (edx) // output registers
        : "a" (0)                            // input: set EAX to 0
    );
    // The CPU vendor string is returned in EBX (genu), EDX(inel), and ECX(ntel)
    *(uint32_t*)(vendor) = ebx;
    *(uint32_t*)(vendor + 4) = edx;
    *(uint32_t*)(vendor + 8) = ecx;
    
    // always null-terminate a C string
    vendor[12] = '\0';
}