#include <avr/io.h>
#include "lib/uart_com.h"
#include "lib/sram.h"
#include <stdio.h>
#include <stdlib.h>
#include "lib/ADC_Driver.h"

#define F_CPU 4915200 //Clock Speed
#include <util/delay.h>

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void main()
{
		uart_init(MYUBRR);
		adc_init();

		//Setup for using external memory space
		MCUCR |= (0x1 << SRE);
		SFIOR |= (0x1 << XMM2);
		printf("\033[2j");

		while (1)
		{
				adc_test();
				_delay_ms(10);
		}
}
