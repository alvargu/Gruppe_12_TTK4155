//Functions, procedures, and types used to find the position of the joystick.

#include "ADC_Driver.h"
#include "joystick.h"
#include <stdio.h>

#define F_CPU 4915200 //Clock Speed
#include <util/delay.h>

static raw_adc_data_t calibration_data = {0u, 0u, 0u, 0u};

//Initialises joystick (runs calibration)
void joystick_init_calibration(void)
{
		raw_adc_data_t adc_readout = {0u, 0u, 0u, 0u};

		uint16_t x_joystick_sum = 0u;
		uint16_t y_joystick_sum = 0u;

		printf("\r");
		printf("Starting calibration\n\r");

		for (int counter = 0; counter < 50; counter++)
		{
				_delay_ms(1); //If no delay, code runs faster than ADC can update
				
				adc_sample(&adc_readout);

				x_joystick_sum += adc_readout.joystick_x;
				y_joystick_sum += adc_readout.joystick_y;
		}

		calibration_data.joystick_x = (uint8_t) (x_joystick_sum / 50u);
		calibration_data.joystick_y = (uint8_t) (y_joystick_sum / 50u);

		printf("Calibration done\n\r");
		printf("Found center value X: %8d\n\r", calibration_data.joystick_x);
		printf("Found center value Y: %8d\n\r", calibration_data.joystick_y);
}

//Calculates the calibrated angle (in percent) for a given joystick readout and calibration value.
static int8_t calculate_calibration(uint8_t readout, uint8_t calibration_value)
{
		int8_t return_val;
		if (readout == calibration_value)
		{
				return_val = 0;
		}
		else if (readout > calibration_value)
		{
				return_val = 100 * (int8_t) (readout - calibration_value) / (255u - calibration_value);
		}
		else
		{
				uint8_t intermediary = 100u* (calibration_value - readout) / calibration_value;
				return_val = -1 * (int8_t) intermediary;
		}
		return return_val;
}

//Puts the calibrated angle of the joystick in the variable pointed to
//by output_p, based on the data in adc_readout_p
void joystick_get_angle(joystick_angle_t *output_p, const raw_adc_data_t *adc_readout_p)
{
		output_p -> x_angle = calculate_calibration(adc_readout_p -> joystick_x, calibration_data.joystick_x);
		output_p -> y_angle = calculate_calibration(adc_readout_p -> joystick_y, calibration_data.joystick_y);
}


