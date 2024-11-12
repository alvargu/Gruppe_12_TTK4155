//Functions, procedures, and types used to find the position of the joystick.

#include "ADC_Driver.h"
#include "joystick.h"
#include <stdio.h>
#include "can_com.h"
#include <avr/io.h>

#define F_CPU 4915200 //Clock Speed
#include <util/delay.h>

static raw_adc_data_t calibration_data = {0u, 0u, 0u, 0u}; //Stores the calibration data that the other functions use

//Initialises joystick (runs calibration)
//Also sets up Pin D4 to detect button press.
void joystick_init_calibration(void)
{
		raw_adc_data_t adc_readout = {0u, 0u, 0u, 0u};

		uint16_t x_joystick_sum = 0u;
		uint16_t y_joystick_sum = 0u;

		printf("\r");
		printf("Starting joystick calibration\n\r");

		for (int counter = 0; counter < 50; counter++)
		{
				_delay_ms(1); //If no delay, code runs faster than ADC can update
				
				adc_sample(&adc_readout);

				x_joystick_sum += adc_readout.joystick_x;
				y_joystick_sum += adc_readout.joystick_y;
		}

		calibration_data.joystick_x = (uint8_t) (x_joystick_sum / 50u);
		calibration_data.joystick_y = (uint8_t) (y_joystick_sum / 50u);

		//Button press pin:
		DDRD &= ~(0x1 << DDD4); //Set Pin D4 as input
		PORTD |= (0x1 << PD4); //Enable pull-up on Pin D4
}

//Calculates the calibrated angle (in percent) for a given joystick readout and calibration value.
static int8_t calculate_calibration(uint8_t readout, uint8_t calibration_value)
//Calibrates differently for above and below the "zero value".
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


#define X_READ ((adc_readout_p -> joystick_x))
#define Y_READ ((adc_readout_p -> joystick_y))
#define X_0 ((calibration_data.joystick_x))
#define Y_0 ((calibration_data.joystick_y))

//Returns the enumerated direction of the joystick, 
//based on the data in adc_readout_p
joystick_direction_t joystick_get_direction(const raw_adc_data_t *adc_readout_p)
{
		joystick_direction_t joystick_state = neutral;

		if ((Y_READ > Y_0 + 15u) && (Y_READ > (X_READ + 1u)) && (Y_READ > (X_0 - X_READ + 1u)))
		{
				joystick_state = up;
		}
		else if ((X_READ > X_0 + 15u) && (X_READ > (Y_READ + 1u)) && (X_READ > (Y_0 - Y_READ + 1u)))
		{
				joystick_state = right;
		}
		else if ((Y_READ < Y_0 - 15u) && (Y_READ < (X_READ - 1u)) && (Y_READ < (X_0 - X_READ - 1u)))
		{
				joystick_state = down;
		}
		else if ((X_READ < X_0 - 15u) && (X_READ < (Y_READ - 1u)) && (X_READ < (Y_0 - Y_READ - 1u)))
		{
				joystick_state = left;
		}

		return joystick_state;
}

void joystick_can_send(void)
{
		uint8_t x_normalized;
		uint8_t	y_normalized;
		joystick_angle_t joyangle;
		can_message_t message = {10u,2u,{0u,0u}};

		raw_adc_data_t adc_readout;
		adc_sample(&adc_readout);

		joystick_get_angle(&joyangle, &adc_readout);

		x_normalized = (joyangle.x_angle + 100);
		y_normalized = (joyangle.y_angle + 100);

		message.data[0] = x_normalized;
		message.data[1] = y_normalized;

		can_transmit(&message,0);
}

