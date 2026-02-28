#include "../include/ata.h"
#include "../include/io.h"

// wait until the drive clears the "busy" bit
void ata_wait_bsy() {
    while (inb(0x1F7) & 0x80);
}

// wait until the drive sets the "data request ready" bit
void ata_wait_drq() {
    while (!(inb(0x1F7) & 0x08));
}

void ata_read_sector(uint32_t lba, uint8_t* buffer) {
    ata_wait_bsy();
    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F)); // master drive & highest 4 bits of LBA
    outb(0x1F2, 1);                           // read 1 sector
    outb(0x1F3, (uint8_t) lba);               // low 8 bits
    outb(0x1F4, (uint8_t)(lba >> 8));         // mid 8 bits
    outb(0x1F5, (uint8_t)(lba >> 16));        // high 8 bits
    outb(0x1F7, 0x20);                        // command: read w/ retry

    ata_wait_bsy();
    ata_wait_drq();
    // 512 bytes in total
    uint16_t* ptr = (uint16_t*) buffer;
    for (int i = 0; i < 256; i++) {
        ptr[i] = inw(0x1F0);
    }
}

void ata_write_sector(uint32_t lba, uint8_t* buffer) {
    ata_wait_bsy();
    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F)); 
    outb(0x1F2, 1);                           
    outb(0x1F3, (uint8_t) lba);               
    outb(0x1F4, (uint8_t)(lba >> 8));         
    outb(0x1F5, (uint8_t)(lba >> 16));        
    outb(0x1F7, 0x30);                        // command: write w/ history

    ata_wait_bsy();
    ata_wait_drq();

    uint16_t* ptr = (uint16_t*) buffer;
    for (int i = 0; i < 256; i++) {
        outw(0x1F0, ptr[i]);
    }
    // save immediately to disk
    outb(0x1F7, 0xE7);
    ata_wait_bsy();
}