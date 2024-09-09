//NOTE: Code is heavily inspired by code found in the Atmega162 datasheet.
#include <avr/io.h>
#include <avr/common.h>
#include "uart_com.h"

//Initialises UART communication.
//Takes in a given UBRR value. (UART Baud Rate Register)
void uart_init(unsigned int ubbr)
{
		//Set baud rate:
		UBRR0H = (unsigned char) (ubbr >> 8);
		UBRR0L = (unsigned char) ubbr;

		//Enable receiver and transmitter:
		UCSR0B = (1 << RXEN0) | (1 << TXEN0);

		//Set frame format: 8data, 2stop bit:
		UCSR0C = (1<<URSEL0) | (1<<USBS0) | (3<<UCSZ00);
		fdevopen(uart_transmit,uart_read);
}

//Transmits one character over UART
//Takes in the character to transmit
void uart_transmit(unsigned char data)
{
		// Wait for empty transmit buffer
		while ( !( UCSR0A & (1<<UDRE0)) )
		{
				; //Do nothing
		}
		// Put data into buffer, sends the data
		UDR0 = data;
}

//Recieves one character from UART
unsigned char uart_read(void)
{
		// Wait for data to be received
		while ( !(UCSR0A & (1<<RXC0)) )
		{
				; //Do nothing
		}
		// Get and return received data from buffer
		return UDR0;
}
