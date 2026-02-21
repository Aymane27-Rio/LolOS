#include "../include/cmos.h"
#include "../include/io.h"

// read a byte from the specified RTC register
uint8_t read_rtc(uint8_t reg) {
    outb(0x70, reg);
    return inb(0x71);
}

// convert BCD to binary, since the RTC stores time in BCD format
uint8_t bcd_to_binary(uint8_t bcd) {
    return ((bcd & 0xF0) >> 1) + ((bcd & 0xF0) >> 3) + (bcd & 0xf);
}

uint8_t get_rtc_seconds() { return bcd_to_binary(read_rtc(RTC_SECONDS)); }
uint8_t get_rtc_minutes() { return bcd_to_binary(read_rtc(RTC_MINUTES)); }
uint8_t get_rtc_hours()   { return bcd_to_binary(read_rtc(RTC_HOURS)); }
uint8_t get_rtc_day()     { return bcd_to_binary(read_rtc(RTC_DAY)); }
uint8_t get_rtc_month()   { return bcd_to_binary(read_rtc(RTC_MONTH)); }
uint8_t get_rtc_year()    { return bcd_to_binary(read_rtc(RTC_YEAR)); }