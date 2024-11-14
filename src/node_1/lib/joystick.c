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

		uint32_t x_joystick_sum = 0u;
		uint32_t y_joystick_sum = 0u;

		printf("\r");
		printf("Starting joystick calibration\n\r");

		uint16_t counter;

		//Large number of samples for calibration to avoid
		//joystick drift on DC motors.
		for (counter = 0; counter < 4000; counter++)
		{
				_delay_ms(1); //If no delay, code runs faster than ADC can update
				
				adc_sample(&adc_readout);

				x_joystick_sum += adc_readout.joystick_x;
				y_joystick_sum += adc_readout.joystick_y;
		}

		calibration_data.joystick_x = (uint8_t) (x_joystick_sum / counter);
		calibration_data.joystick_y = (uint8_t) (y_joystick_sum / counter);

		printf("x calibration value: %d\n\r", calibration_data.joystick_x);
		printf("y calibration value: %d\n\r", calibration_data.joystick_y);

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


static uint8_t joyangle_normalized_clamp(uint8_t joyangle_normed)
{
		//clamp/sanitize the value to avoid problems around
		//the middle point

		if ((joyangle_normed > 95u) && (joyangle_normed < 105u))
		{
				joyangle_normed = 100u;
		}

		return joyangle_normed;
}


void joystick_can_send(void)
{
		uint16_t x_normalized_sum = 0;
		uint16_t y_normalized_sum = 0;

		uint8_t x_normed_averaged;
		uint8_t y_normed_averaged;
		
		can_message_t message = {10u,3u,{0u,0u,0u}};
		raw_adc_data_t adc_readout;
		joystick_angle_t joyangle;

		uint8_t i;
		for (i=0;i<=150;i++)
		{
				adc_sample(&adc_readout);

				joystick_get_angle(&joyangle, &adc_readout);

				x_normalized_sum += (joyangle.x_angle + 100);
				y_normalized_sum += (joyangle_normalized_clamp(joyangle.y_angle + 100));
		}

		x_normed_averaged = (uint8_t) (x_normalized_sum / i);
		y_normed_averaged = (uint8_t) (y_normalized_sum / i);

		x_normed_averaged = joyangle_normalized_clamp(x_normed_averaged);
		y_normed_averaged = joyangle_normalized_clamp(y_normed_averaged);

		printf("x normed average: %d | y normed average: %d\n\r", x_normed_averaged, y_normed_averaged);

		message.data[0] = x_normed_averaged;
		message.data[1] = y_normed_averaged;

		//add button pressed state to message
		//Button pressed corresponds to "logic low" on pin 4
		
		message.data[2] = (uint8_t) (!((PIND >> PD4) & 0x1));

		can_transmit(&message,0);
}

