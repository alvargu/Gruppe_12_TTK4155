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
		volatile char *adc_start_address = (char *) 0x1400; //0x1400 is the first adress in the adress space.
		raw_adc_data_t adc_inputs;

		adc_start_address[0] = 0x00; //Write any value just to send write signal to ADC.

	    //For read and write, the adress does not matter as long as it is within the ADC adress space
		//The order of reads matters here, as the ADC inputs are stored in the ADC's RAM in a certain order (Pin 0 -> Pin 3).
		//Reading "pops" values from the RAM in FIFO order.
		adc_inputs.joystick_x = adc_start_address[0];
		adc_inputs.joystick_y = adc_start_address[0];
		adc_inputs.slider_left = adc_start_address[0];
		adc_inputs.slider_right = adc_start_address[0];

		printf("\r");
		printf("x : %8d | y: %8d || left: %8d | right: %8d", inputs.joystick_x, inputs.joystick_y, inputs.slider_right, inputs.slider_left);
}

//Samples current values from the ADC
void adc_sample(raw_adc_data_t* adc_inputs) //Untested as of now
{
		volatile char *adc_start_address = (char *) 0x1400; //0x1400 is the first adress in the adress space.
		adc_start_address[0] = 0x00; //Write any value just to send write signal to ADC.

	    //For read and write, the adress does not matter as long as it is within the ADC adress space
		//The order of reads matters here, as the ADC inputs are stored in the ADC's RAM in a certain order (Pin 0 -> Pin 3).
		//Reading "pops" values from the RAM in FIFO order.
		adc_inputs -> joystick_x = adc_start_address[0];
		adc_inputs -> joystick_y = adc_start_address[0];
		adc_inputs -> slider_left = adc_start_address[0];
		adc_inputs -> slider_right = adc_start_address[0];
}

