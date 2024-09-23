//Procedures, functions, and types used to initialise everything needed for ADC, and read values from ADC.

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "ADC_Driver.h"



//Initialises PD5 as an output pin for PWM, and sets up Counter 3 to
//produce a PWM signal.
void adc_init()
{
		//Setting PD5 to output
		DDRD |= (0x1 << DDD5);

		//Setup for PWM output on PD5
		TCCR1B |= (0x1 << WGM12) | (0x1 << CS10);
		TCCR1A |= (0x1 << COM3A0);
}

//Prints all input values from ADC (should be placed in a loop)
void adc_test()
{
		volatile char *adc_start_address = (char *) 0x1400;
		//uint8_t x_axis, y_axis;
		raw_adc_data_t inputs;

		adc_start_address[0] = 0x00; //Write any value just to send write signal to ADC.
		inputs.joystick_x = adc_start_address[0];
		inputs.joystick_y = adc_start_address[0];
		inputs.slider_left = adc_start_address[0];
		inputs.slider_right = adc_start_address[0];

		printf("\r");
		printf("x : %8d | y: %8d || left: %8d | right: %8d", inputs.joystick_x, inputs.joystick_y, inputs.slider_right, inputs.slider_left);
}

//Samples current values from the ADC
void adc_sample(raw_adc_data_t* raw_adc_data)
{
		//TODO: implement
}

