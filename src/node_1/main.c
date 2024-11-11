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
		printf("%c%c%c%c",0x1B,0x5B,0x32,0x4A); //clear screen
		uart_init(MYUBRR);
		xmem_init();
		adc_init();
		joystick_init_calibration();
		can_init();


		can_message_t msg_send = {15u, 8u, {40u, 5u, 45u, 24u, 12u, 4u, 1u, 254u}};
		can_message_t msg1 = {0u, 1u, {0u}};

		printf("waiting to transmit message\n\r");
		can_transmit(&msg_send, 0);
		printf("message transmitted\n\r");

		while (1){
				joystick_can_send();
		}
}
