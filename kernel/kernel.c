#include <stdint.h>
#include "../include/io.h"
#include "../include/terminal.h"
#include "../include/string.h"
#include "../include/cmos.h"

char get_keypress();

char command_buffer[256];
int buffer_index = 0;

char history[5][256]; // simple command history, stores last 5 commands
int history_index = 0;
int history_count = 0;

void kmain() {
    terminal_init();
    // input loop
    while (1) {
        char key = get_keypress();
        if (key !=0){
            if (key == '\n') {
                print_char('\n');
                command_buffer[buffer_index] = '\0'; 
            
                if (buffer_index > 0){

                    strcpy(history[history_count % 5], command_buffer);
                    history_count++;
                    history_index = history_count;

                    char* args = 0;
                    for (int i =0; i < buffer_index; i++){
                        if (command_buffer[i]== ' '){
                            command_buffer[i]='\0';
                            args = &command_buffer[i+1];
                            break;
                        }
                    }
                    if (strcmp(command_buffer, "help")==0){
                        print_string("Available commands: help, clear, echo, theme, reboot, shutdown, time, date\n");
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
                        else if (strcmp(command_buffer, "theme") == 0) {
                            if (args == 0) {
                                print_string("Usage: theme [green|blue|red|default]\n");
                            } 
                            else if (strcmp(args, "green") == 0) {
                                terminal_apply_theme(0x0A); 
                            }
                            else if (strcmp(args, "blue") == 0) {
                                terminal_apply_theme(0x09); 
                            }
                            else if (strcmp(args, "red") == 0) {
                                terminal_apply_theme(0x0C); 
                            }
                            else if (strcmp(args, "default") == 0) {
                                terminal_apply_theme(0x0F); 
                            }
                            else {
                                print_string("Unknown theme. Try: green, blue, red, default\n");
                            }
                        }
                        else if (strcmp(command_buffer, "time") == 0) {
                            print_string("Current Time: ");
                            print_time_number(get_rtc_hours());
                            print_char(':');
                            print_time_number(get_rtc_minutes());
                            print_char(':');
                            print_time_number(get_rtc_seconds());
                            print_string(" (UTC)\n");
                    }
                        else if (strcmp(command_buffer, "date") == 0) {
                            print_string("Current Date: ");
                            print_time_number(get_rtc_day());
                            print_char('/');
                            print_time_number(get_rtc_month());
                            print_string("/20"); // The RTC year is 2 digits (e.g., 26 for 2026)
                            print_time_number(get_rtc_year());
                            print_char('\n');
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
                // up arrow for command history
                else if (key == 17){
                    if (history_count > 0 && (history_count - history_index) < 5 && history_index > 0) {
                        for (int i = 0; i < buffer_index; i++) print_char('\b');
                        history_index--;
                        strcpy(command_buffer, history[history_index % 5]);
                        buffer_index = strlen(command_buffer);
                        print_string(command_buffer);
                }
                }
                // down arrow for command history
                else if (key == 18){
                    if (history_index < history_count) {
                        for (int i = 0; i < buffer_index; i++) print_char('\b');
                        history_index++;
                        if (history_index == history_count) {
                            command_buffer[0] = '\0';
                            buffer_index = 0;
                        } else {
                            strcpy(command_buffer, history[history_index % 5]);
                            buffer_index = strlen(command_buffer);
                            print_string(command_buffer);
                        }
                }

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
