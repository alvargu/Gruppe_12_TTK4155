#ifndef MOTOR_H
#define MOTOR_H

#include "sam.h"
#include <stdint.h>
#include "time.h"
#include "pwm_ctrl.h"

void motor_init(void);
void motor_return_to_zero(void);
void motor_speed_set(int8_t motor_speed);

#endif