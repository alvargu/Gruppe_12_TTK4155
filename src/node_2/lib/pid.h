#ifndef PID_H
#define PID_H

#include <stdint.h>
#include "time.h"
#include "encoder.h"

#define TIMING_FACTOR 1				//Update

// Define
typedef struct {
	int8_t kp;
	int8_t ti;
	int8_t td;
	int8_t e_factor;
	int16_t integral_value;
} PID;

void pid_init(uint8_t kp, uint8_t ti, uint8_t td);
void pid_get_u(uint8_t error);

uint8_t p_part(uint8_t);
uint8_t i_part(uint8_t);
uint8_t d_part(uint8_t);

uint16_t integrator(uint8_t);

#endif