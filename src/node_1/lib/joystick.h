//Functions, procedures, and types used to find the position of the joystick.

#include <stdint.h>
#include "ADC_Driver.h"

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
} joystick_direction;

//Initialises joystick (runs calibration)
void joystick_init_calibration(void);

//Gets the calibrated angle of the joystick
void joystick_get_angle(joystick_angle_t*, raw_adc_data_t*);

//Gets the direction of the joystick. 
joystick_direction joystick_get_direction(raw_adc_data_t*);

