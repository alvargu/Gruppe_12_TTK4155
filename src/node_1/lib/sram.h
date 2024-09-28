#ifndef SRAM_H
#define SRAM_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

#include "uart_com.h"

#define SRAM_OLED   0x1000
#define SRAM_ADC    0x1400
#define SRAM_MEM    0x1800

bool sram_check (void);
bool sram_write (uint8_t*, uint8_t*);
bool sram_read  (uint8_t*);

#endif