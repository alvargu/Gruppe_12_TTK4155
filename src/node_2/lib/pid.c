#include "pid.h"

//File is named pid, but the design has changed such that 
//it is now a PI controller.

// Instantiate pid struct for global values
PID pid;

uint64_t timing_var_i = 0;
uint64_t timing_var_d = 0;


volatile int16_t error_sum = 0;

// Initialize PID controller parameters
void pid_init(float kp, float ti, float td) {
	pid.kp = kp;
	pid.ti = ti;
}

int16_t pid_get_u(int16_t error)
{
	if(error <= 14 && error >= -14)
	{
		error_sum += error;

		return pid.kp * error + (pid.ti * error_sum / 128);		
	}
	//return 0;
}