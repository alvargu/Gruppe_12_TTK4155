//Procedures and functions used to initialise everything needed for ADC, and read values from ADC.

#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

#include <stdint.h>

typedef struct raw_adc_data_t
{
		uint8_t joystick_x;
		uint8_t joystick_y;
		uint8_t slider_left;
		uint8_t slider_right;
} raw_adc_data_t;

//Initialises PD5 as an output pin for PWM, and sets up Counter 3 to
//produce a PWM signal.
void adc_init();

//Prints all input values from ADC (should be placed in a loop)
void adc_test();

//Samples current values from the ADC
void adc_sample(raw_adc_data_t* raw_adc_data);

#endif
