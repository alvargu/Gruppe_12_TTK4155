//Functions, procedures, and types used to find the position of the joystick.

#include <stdint.h>
#include "ADC_Driver.h"

#ifndef JOYSTICK_H
#define JOYSTICK_H

typedef struct //Joystick angle in x and y direction, with the angle as a percentage (from -100 to 0, from 0 to +100).
{
		//Note that these are signed values
		int8_t x_angle;
		int8_t y_angle;
} joystick_angle_t;

typedef enum
{
		left,
		right,
		up,
		down,
		neutral
} joystick_direction_t;

//Initialises joystick (runs calibration)
void joystick_init_calibration(void);

//Puts the calibrated angle of the joystick in the variable pointed to
//by output_p, based on the data in adc_readout_p
void joystick_get_angle(joystick_angle_t *input_p, const raw_adc_data_t *adc_readout_p);

//Returns the enumerated direction of the joystick, 
//based on the data in adc_readout_p
joystick_direction_t joystick_get_direction(const raw_adc_data_t*);

#endif
