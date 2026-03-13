#ifndef MOUSE_H
#define MOUSE_H
#include <stdint.h>

extern int32_t mouse_x;
extern int32_t mouse_y;
extern uint8_t left_click;
void mouse_init();
int handle_mouse_packet();

#endif