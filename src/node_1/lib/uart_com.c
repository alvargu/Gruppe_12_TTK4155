#include "uart_com.h"

void UART_INIT(unsigned int ubrr){
	UBRR0H = (unsigned char)(ubrr >> 8);
	
	UBRR0L = (unsigned char)ubrr;
	
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	
	UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);
	
	fdevopen(UART_TRANSMIT,UART_READ);
}

void UART_TRANSMIT(unsigned char c){
	while (!(UCSR0A & (1<<UDRE0))){
		;
	}
	/* Put data into buffer, sends the data */
	UDR0 = c;
}

uint8_t UART_READ(void){
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) ){
		;
	}
	/* Get and return received data from buffer */
	return UDR0;
}
