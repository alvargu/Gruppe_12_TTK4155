#include <avr/io.h>
#include "lib/uart_com.h"
#include "lib/xmem.h"
#include <stdio.h>
#include <stdlib.h>
#include "lib/ADC_Driver.h"
#include "lib/can_com.h"

#define F_CPU 4915200 //Clock Speed
#include <util/delay.h>

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void main()
{
		uart_init(MYUBRR);
		adc_init();

		can_init();
		
		can_message_t msg1 = {4u, 8u, {40u, 5u, 60u, 24u, 12u, 4u, 1u, 254u}};
		can_message_t msg2 = {45u, 4u, {40u, 58u, 60u, 124u, 12u, 4u, 1u, 254u}};

		while (1)
		{
				can_transmit(&msg1, 0);
				_delay_ms(500);
				can_transmit(&msg2, 0);
				_delay_ms(500);

		}
}
