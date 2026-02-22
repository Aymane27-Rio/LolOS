#include "../include/terminal.h"
#include "../include/shell.h"


void kmain(){
    terminal_init();
    start_shell();
    __asm__ volatile("cli; hlt"); //just in case
}