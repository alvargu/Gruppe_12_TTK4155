#include <avr/io.h>
#include "lib/uart_com.h"
#include "lib/xmem.h"
#include <stdio.h>
#include <stdlib.h>
#include "lib/ADC_Driver.h"
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

		//Clear screen:
		printf("%c%c%c%c",0x1B,0x5B,0x32,0x4A);

		joystick_angle_t current_angle = {0, 0};
		raw_adc_data_t adc_readout = {0u, 0u, 0u, 0u};
		
		while (1)
		{
				printf("\r");
				adc_sample(&adc_readout);
				joystick_get_angle(&current_angle, &adc_readout);

				printf("X angle: %4d | Y angle: %4d", current_angle.x_angle, current_angle.y_angle);
		}
}
