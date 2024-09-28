#ifndef OLED_CTRL_H
#define OLED_CTRL_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#define TIMER_VAL 40960

void oled_init();

#endif