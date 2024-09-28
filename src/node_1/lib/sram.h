#ifndef SRAM_H
#define SRAM_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <avr/io.h>

#include "uart_com.h"

#define SRAM_OLED			0x1000
#define SRAM_OLED_COM		0x1000
#define SRAM_OLED_DATA		0x1200
#define SRAM_ADC			0x1400
#define SRAM_MEM			0x1800
#define SRAM_OLED_COM_END	0x11FF
#define SRAM_OLED_DATA_END	0x13FF
#define SRAM_OLED_END		0x13FF
#define SRAM_ADC_END		0x17FF
#define SRAM_MEM_END		0x1FFF

bool	sram_init	(void);
void    sram_write	(uint16_t mem_loc, uint8_t adrr, uint8_t val);
uint8_t sram_read	(uint16_t mem_loc, uint8_t adrr);

#endif