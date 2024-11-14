#ifndef PID_H
#define PID_H

#include <stdint.h>
#include "time.h"
#include "encoder.h"


void pid_init(uint8_t kp, uint8_t ki, uint8_t kd);
void pid_get_u(uint8_t error);

#endif