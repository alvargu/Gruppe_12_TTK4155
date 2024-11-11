#ifndef PWM_CTRL
#define PWM_CTRL

#include "sam.h"

#define PWM_MIN 90
#define PWM_MAX 210

void pwm_init();
void pwm_udc(uint16_t);
void pwm_upv(uint16_t);
void pwm_udt(uint16_t);
void pwm_apply_timings();
void default_values();
 
#endif