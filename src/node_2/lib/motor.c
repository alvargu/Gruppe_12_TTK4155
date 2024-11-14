
#include "motor.h"

uint64_t start_timer_reset = 0; 

void motor_init(void)
{
     // Enable the PIO controller for PORT C
	// PIO_PC23 => PIN134 (Motor PHASE/DIRECTION Pin)
	PIOC->PIO_PER |= MOTOR_DIRECTION_PIN;  // Enable PIO control
	PIOC->PIO_OER |= MOTOR_DIRECTION_PIN;  // Set PIO to Output Enabled Mode

     // Initialization of PWM signal for motor driver (speed initialized to zero)
     pwm_motor_init();
}

void motor_return_to_zero(void)
{
     start_timer_reset = time_now();
	 while (time_now() < (start_timer_reset + MOTOR_CALIB_DELAY))
	 {
		motor_speed_set(140);
	 }
	 motor_speed_set(100);
}

void motor_dirset_L(void)
{
     PIOC->PIO_SODR |= MOTOR_DIRECTION_PIN;
}

void motor_dirset_R(void)
{
     PIOC->PIO_CODR |= MOTOR_DIRECTION_PIN;
}

void motor_speed_set(int8_t motor_speed)
{
     // Input sanitizer for clamping around min-, max-  and zero-values
     if (motor_speed < _MOTOR_SPEED_MIN)
	{
		motor_speed = _MOTOR_SPEED_MIN; 
	} 
    else if (motor_speed > _MOTOR_SPEED_MAX) 
	{
		motor_speed = _MOTOR_SPEED_MAX;	 
	}
	if ((motor_speed < MOTOR_BUFFER_MAX) && (motor_speed > MOTOR_BUFFER_MIN))
	{
		motor_speed = 100;
	}
	
    // Calculate duty_cycle from absolute value of motor speed
    uint16_t duty_cycle = 0;
	uint16_t temp_val = motor_speed;
    // Set motor direction based on positive or negative speed input
    if (temp_val < 100) 
	{
		motor_dirset_R();	 
		duty_cycle =  (_MOTOR_DC_MAX*(100 - motor_speed))/100;
	}
	else if (temp_val > 100) 
	{
		motor_dirset_L();
		duty_cycle =  (_MOTOR_DC_MAX*(motor_speed - 100))/100;	
	}
	//printf("%d\n\r",duty_cycle);
	pwm_set_motor_speed(duty_cycle);
}