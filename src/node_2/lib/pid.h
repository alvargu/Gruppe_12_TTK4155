#ifndef PID_H
#define PID_H

#include <stdint.h>
#include "time.h"
#include "encoder.h"

// Define 
typedef struct {
	int8_t kp;
	int8_t ki;
	int8_t kd;
	int16_t integral_value;
	int8_t e_factor;
} PID;

void pid_init(uint8_t kp, uint8_t ki, uint8_t kd);
void pid_get_u(uint8_t error);

#endif