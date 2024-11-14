#include "motor.h"

uint64_t start_timer_reset = 0; 

void motor_init(void)
{
    // Enable the PIO controller for PORT C
	// PIO_PC23 => PIN134 (Motor PHASE/DIRECTION Pin)
	PIOC->PIO_PER |= _MOTOR_DIRECTION_PIN;  // Enable PIO control
	PIOC->PIO_OER |= _MOTOR_DIRECTION_PIN;  // Set PIO to Output Enabled Mode

     // Initialization of PWM signal for motor driver (speed initialized to zero)
     pwm_motor_init();
}

void motor_return_to_zero(void){
     start_timer_reset = time_now();
	 while (time_now() < (start_timer_reset + MOTOR_CALIB_DELAY))
	 {
		motor_speed_set(-300);
	 }
	 motor_speed_set(0);
}

void motor_dirset_L(void)
{
     PIOC->PIO_CODR |= _MOTOR_DIRECTION_PIN;
}

void motor_dirset_R(void)
{
     PIOC->PIO_SODR |= _MOTOR_DIRECTION_PIN;
}

void motor_speed_set(int16_t motor_speed)
{
    // Input sanitizer for clamping around min-, and max zero-values
    
	if (motor_speed < _MOTOR_SPEED_MIN)
	{
		motor_speed = _MOTOR_SPEED_MIN; 
	} 
    else if (motor_speed > _MOTOR_SPEED_MAX) 
	{
		motor_speed = _MOTOR_SPEED_MAX;	 
	}
	
    // Calculate duty_cycle from absolute value of motor speed
    uint16_t duty_cycle = 0;
    // Set motor direction based on positive or negative speed input
    if (motor_speed < 0) 
	{
		motor_dirset_L();	 
		duty_cycle =  - (_MOTOR_DC_MAX*(motor_speed))/700;
	}
	else if (motor_speed >= 0) 
	{
		motor_dirset_R();
		duty_cycle =  (_MOTOR_DC_MAX*(motor_speed))/700;	
	}
	//printf("%d\n\r",duty_cycle);
	pwm_set_motor_speed(duty_cycle);
}
