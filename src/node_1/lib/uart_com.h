#pragma			once
#include		<avr/io.h>

#define			FOSC	4915200
#define			BAUD	9600
#define			MYUBRR	FOSC/16/BAUD-1

uint8_t			UART_READ(void);
void			UART_TRANSMIT(unsigned char);
void			UART_INIT(unsigned int);