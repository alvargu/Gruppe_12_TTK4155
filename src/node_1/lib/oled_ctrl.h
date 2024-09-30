#ifndef OLED_CTRL_H
#define OLED_CTRL_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#define TIMER_VAL	10240
#define F_CPU		4915200

void oled_init();
void oled_clear();
void oled_printf(uint8_t*);

#endif