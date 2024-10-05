#ifndef OLED_CTRL_H
#define OLED_CTRL_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#include "xmem.h"

#define OLED_WIDTH      128
#define OLED_LINE_CNT   8

void oled_init();
void oled_clear();

//TODO: Working on

//Move OLED "Cursor"
void oled_home();
void oled_pos(uint8_t, uint8_t);
void oled_goto_line(uint8_t);
void oled_goto_column(uint8_t);

//Clear OLED display
void oled_clear_line(uint8_t);
void oled_clear_column(uint8_t);

//Print a char to the display
void oled_print_char(char*);

#endif