
#include "src\node_2\lib\motor.h"

#define _MOTOR_PHASE_PIN PIO_PC23
#define _MOTOR_UPDATE_INTERVAL msecs(50)
#define _MOTOR_SPEED_MIN (-100)
#define _MOTOR_SPEED_MAX 100
#define _MOTOR_DC_MAX 2050
#define _MOTOR_DC_MIN 0


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
     // Set mot
     motor_speed_set(-2);

     time_now();
}

void motor_dirset_L(void)
{
     PIOC->PIO_SODR |= _MOTOR_DIRECTION_PIN;
}

void motor_dirset_R(void)
{
     PIOC->PIO_CODR |= _MOTOR_DIRECTION_PIN;
}

void motor_speed_set(int8_t motor_speed)
{
     // Timer -----
	// Because Motor Driver can be updated to fast, and it takes MINIMUM 20 ms for Motor Driver to activate
	// Before we do anything, we must ensure proper amount of time from previous servo time
	if ((time_now() - start_timer_reset) < _MOTOR_UPDATE_INTERVAL) {
		return;  // Exit if the interval hasn't passed yet
	}
	start_timer_reset = time_now(); // Update timer

     // Make sure input value is within range
     if (motor_speed < _MOTOR_SPEED_MIN) motor_speed = _MOTOR_SPEED_MIN;
     if (motor_speed > _MOTOR_SPEED_MAX) motor_speed = _MOTOR_SPEED_MAX; 

     // Calculate duty_cycle from absolut value of motor speed
     uint16_t duty_cycle =  _MOTOR_DC_MAX*abs(motor_speed)/100;

     // Set motor direction based on positive or negative speed input
     if (motor_speed < 0) motor_dirset_R();
     if (motor_speed > 0) motor_dirset_L();

     pwm_motor_speed_set(duty_cycle);
}