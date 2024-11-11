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
#include "lib/joystick.h"


#define F_CPU 4915200 //Clock Speed
#include <util/delay.h>

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void main()
{
		uart_init(MYUBRR);
		xmem_init();
		adc_init();
		joystick_init_calibration();
		can_init();

		printf("%c%c%c%c",0x1B,0x5B,0x32,0x4A); //clear screen

		can_message_t msg_send = {15u, 8u, {40u, 5u, 45u, 24u, 12u, 4u, 1u, 254u}};
		can_message_t msg1 = {0u, 1u, {0u}};
		can_message_t msg2 = {0u, 1u, {0u}};
		can_message_t msg3 = {0u, 1u, {0u}};
		can_message_t msg4 = {0u, 1u, {0u}};

		printf("Transmitting message\n\r");

		can_transmit(&msg_send, 0);


		can_receive(&msg1);
		can_receive(&msg2);
		can_receive(&msg3);
		can_receive(&msg4);


		printf("message 1:\n\r");
		printf("Received data: %d\r\n",msg1.data[1]);
		printf("ID of received message: %d\r\n",msg1.id);
		printf("Len of received message: %d\r\n",msg1.data_len);

		printf("message 2:\n\r");
		printf("Received data: %4d\r\n",msg2.data[2]);
		printf("ID of received message: %8d\r\n",msg2.id);
		printf("Len of received message: %8d\r\n",msg2.data_len);

		printf("message 3:\n\r");
		printf("Received data: %d\r\n",msg3.data[3]);
		printf("ID of received message: %d\r\n",msg3.id);
		printf("Len of received message: %d\r\n",msg3.data_len);

		printf("message 4:\n\r");
		printf("Received data: %d\r\n",msg4.data[4]);
		printf("ID of received message: %d\r\n",msg4.id);
		printf("Len of received message: %d\r\n",msg4.data_len);

		while (1);
}
