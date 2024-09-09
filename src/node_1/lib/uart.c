#include <avr/io.h>
#include <stdio.h>

#include "uart_com.h"

int main(void)
{
    UART_INIT(MYUBRR);
	uint8_t a = '@';
    while (1) 
    {
		scanf("%c", &a);
		printf("%c",a);
    }
}