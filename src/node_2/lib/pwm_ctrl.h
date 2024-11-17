#ifndef PWM_CTRL
#define PWM_CTRL
#include "sam.h"

#define F_CPU 84000000

#define PWM_FRQ	50
#define PWM_MS	F_CPU/512						
#define PWM_MIN PWM_MS/PWM_FRQ/20*9/10			
#define PWM_MAX PWM_MS/PWM_FRQ/20*21/10			

#define PWM_MOTOR_PER F_CPU/1024/40

//#define PWM_LEFT	PWM_MS/PWM_FRQ/20			
//#define PWM_RIGHT	PWM_MS/PWM_FRQ/20*2			
//#define PWM_CENTER	PWM_MS/PWM_FRQ/20*15/10		

#define JOYSTICK_VAL_RANGE 200

void tc_init(void);

void pwm_init(void);
void pwm_update_duty_cycle(uint16_t);
void pwm_update_period_value(uint16_t);
void pwm_update_dead_time(uint16_t);
uint16_t pwm_scale(uint16_t);
 
void pwm_motor_init(void);
void pwm_set_motor_speed(uint16_t); 
 
#endif
