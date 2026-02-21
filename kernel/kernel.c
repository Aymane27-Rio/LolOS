#include <stdint.h>
#include "../include/io.h"
#include "../include/terminal.h"
#include "../include/string.h"

char get_keypress();


void kmain() {
    terminal_init();
    
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
                    char* args = 0;
                    for (int i =0; i < buffer_index; i++){
                        if (command_buffer[i]== ' '){
                            command_buffer[i]='\0';
                            args = &command_buffer[i+1];
                            break;
                        }
                    }
                    if (strcmp(command_buffer, "help")==0){
                        print_string("Available commands: help, clear, echo, reboot, shutdown\n");
                        } 
                        else if (strcmp(command_buffer, "clear") == 0) {
                            terminal_clear();
                        } 
                        else if (strcmp(command_buffer, "echo") == 0) {
                            if (args != 0) {
                                print_string(args);
                            } 
                            print_char('\n');
                        }
                        else if (strcmp(command_buffer, "reboot") == 0) {
                            print_string("Rebooting system...\n");
                            outb(0x64, 0xFE); // CPU reset command
                        }
                        else if (strcmp(command_buffer, "shutdown") == 0) {
                            print_string("System stopped. You can close the emulator now.\n");
                            __asm__ volatile("cli; hlt"); //nvm
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
        }      
    }