#include <avr/io.h>
#include "lib/uart_com.h"
#include "lib/xmem.h"
#include <stdio.h>
#include <stdlib.h>
#include "lib/ADC_Driver.h"
#include "lib/can_com.h"
#include "lib/spi.h"
#include "lib/can_ctrl.h"
#include "lib/mcp2515.h"

#define F_CPU 4915200 //Clock Speed
#include <util/delay.h>

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void main()
{
		uart_init(MYUBRR);
		adc_init();


		//printf("%c%c%c%c",0x1B,0x5B,0x32,0x4A); //clear screen
		//spi_master_init();

		//_delay_us(100);

		//
		//can_ctrl_reset();

		//															  
		//can_ctrl_write(MCP_CANCTRL, MODE_LOOPBACK);

		//_delay_us(100);
		//uint8_t read_val = can_ctrl_read(MCP_CANSTAT);

		//printf("CANSTAT right after reset: %d\n\r", read_val);

		//while (1);

		printf("%c%c%c%c",0x1B,0x5B,0x32,0x4A); //clear screen
	
		can_init();


		can_message_t msg1 = {30u, 8u, {40u, 5u, 45u, 24u, 12u, 4u, 1u, 254u}};
		can_message_t msg2;

		uint8_t rec = 50;

		can_transmit(&msg1, 0);
		_delay_ms(500);
		//can_transmit(&msg1, 0);
		_delay_ms(500);
		can_receive(&msg2);
		_delay_ms(500);
		//can_receive(&msg2);
		printf("Received data: %4d\r\n",msg2.data[2]);
		printf("ID of received message: %8d\r\n",msg2.id);
		printf("Len of received message: %8d\r\n",msg2.data_len);


		while (1);
}
