//Seems to not work for now.
#include <avr/io.h>
#include "uart_driver.h"

#define FOSC 4915200 //Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void main()
{
		uart_init(MYUBRR);
		unsigned char letter = '0';
		while (1)
		{
				//letter = uart_receive();
				uart_transmit(letter);
		}
}
