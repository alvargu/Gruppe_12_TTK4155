#ifndef XMEM_H
#define XMEM_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <avr/io.h>

#define XMEM_OLED			0x1000
#define XMEM_OLED_COM		0x1000
#define XMEM_OLED_DATA		0x1200
#define XMEM_ADC			0x1400
#define XMEM_SRAM_MEM		0x1800
#define XMEM_OLED_COM_END	0x11FF
#define XMEM_OLED_DATA_END	0x13FF
#define XMEM_OLED_END		0x13FF
#define XMEM_ADC_END		0x17FF
#define XMEM_SRAM_MEM_END	0x1FFF

bool	xmem_init	(void);
void    xmem_write	(uint16_t mem_loc, uint8_t adrr, uint8_t val);
uint8_t xmem_read	(uint16_t mem_loc, uint8_t adrr);

#endif