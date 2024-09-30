//Procedures, functions, and types used to initialise everything needed for ADC, and read values from ADC.

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "ADC_Driver.h"
#include "xmem.h"

static uint8_t adc_read(void)
{
		return xmem_read(XMEM_ADC, 0u); //It never matters which
										//adress in the ADC we 
										//read from, so we just 
										//read from adress 0
}

static void adc_write(void) //We never write a meaningful value to
							//the adc, so the function takes no
							//parameters
{
		xmem_write(XMEM_ADC, 0u, 0u); //It never matters which
}                                     //adress in the ADC we 
                                      //read from, so we just 
                                      //read from adress 0

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
		raw_adc_data_t adc_inputs;
		adc_write();

		//The order of reads matters here, as the ADC inputs are stored in the ADC's RAM in a certain order (Pin 0 -> Pin 3).
		//Reading "pops" values from the ADC's RAM in FIFO order.
		adc_inputs.joystick_x = adc_read();
		adc_inputs.joystick_y = adc_read();
		adc_inputs.slider_left = adc_read();
		adc_inputs.slider_right = adc_read();

		printf("\r");
		printf("x : %8d | y: %8d || left: %8d | right: %8d", adc_inputs.joystick_x, adc_inputs.joystick_y, adc_inputs.slider_right, adc_inputs.slider_left);
}

//Samples current values from the ADC
void adc_sample(raw_adc_data_t* adc_inputs) 
{
		adc_write();
	    //For read and write, the adress does not matter as long as it is within the ADC adress space
		//The order of reads matters here, as the ADC inputs are stored in the ADC's RAM in a certain order (Pin 0 -> Pin 3).
		//Reading "pops" values from the RAM in FIFO order.
		adc_inputs -> joystick_x = adc_read();
		adc_inputs -> joystick_y = adc_read();
		adc_inputs -> slider_left = adc_read();
		adc_inputs -> slider_right = adc_read();
}

