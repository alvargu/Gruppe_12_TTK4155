#ifndef MOTOR_H
#define MOTOR_H

#include "sam.h"
#include <stdint.h>
#include "time.h"
#include "pwm_ctrl.h"
#include <stdio.h>

#define MOTOR_DIRECTION_PIN PIO_PC23
#define MOTOR_UPDATE_INTERVAL msecs(10)
#define MOTOR_SPEED_MIN 0
#define MOTOR_SPEED_MAX 200
#define MOTOR_BUFFER_MAX 105
#define MOTOR_BUFFER_MIN 95
#define MOTOR_DC_MAX 2050
#define MOTOR_DC_MIN 0
#define MOTOR_CALIB_DELAY msecs(2000)

void motor_init(void);
void motor_return_to_zero(void);
void motor_speed_set(uint16_t motor_speed);

#endif