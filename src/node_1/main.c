#include <avr/io.h>
#include "lib/uart_com.h"
#include "lib/sram.h"
#include <stdio.h>

#define F_CPU 4915200 //Clock Speed
#include <util/delay.h>

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void main()
{
		uart_init(MYUBRR);
		unsigned char letter;

		char message[] = "Hei!!!";
		printf("%s",message);

		while (1)
		{
				scanf("%c",&letter);
				printf("%c",letter);
				_delay_ms(10);
		}
}
