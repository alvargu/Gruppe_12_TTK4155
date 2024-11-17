//File is named pid, but the design has changed such that
//it is now a PI controller.


#ifndef PID_H
#define PID_H

#include <stdint.h>
#include "time.h"
#include "encoder.h"

#define TIME_CONSTANT usecs(100)

// Define
typedef struct {
	float kp;
	float ti;
} PID;

void pid_init(float kp, float ti, float td);
int16_t pid_get_u(int16_t error);


#endif
