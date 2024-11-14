#ifndef MOTOR_H
#define MOTOR_H

#include "sam.h"
#include "pwm_ctrl.h"
#include <stdint.h>
#include "time.h"
#include <stdio.h>

#define _MOTOR_DIRECTION_PIN PIO_PC23
#define _MOTOR_UPDATE_INTERVAL msecs(10)
#define _MOTOR_SPEED_MIN (-700)
#define MOTOR_SPEED_CENTER 0
#define _MOTOR_SPEED_MAX 700
#define MOTOR_BUFFER_MAX 20
#define MOTOR_BUFFER_MIN -20
#define _MOTOR_DC_MAX 2050
#define _MOTOR_DC_MIN 0
#define MOTOR_CALIB_DELAY msecs(2000)

void motor_init(void);
void motor_return_to_zero(void);
void motor_speed_set(int16_t motor_speed);

#endif
