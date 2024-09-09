#include <avr/io.h>
#include "lib/uart_com.h"

#define F_CPU 4915200 //Clock Speed
#include <util/delay.h>

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void main()
{
		uart_init(MYUBRR);
		unsigned char letter = 0x41;
		_delay_ms(10);
		while (1)
		{
				letter = uart_read();
				uart_transmit(letter);
				_delay_ms(100);
		}
}
