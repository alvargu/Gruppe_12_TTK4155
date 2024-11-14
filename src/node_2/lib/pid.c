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
	
	error_sum += error;
	
	
	return pid.kp * error + (pid.ti * error_sum / 128);
	
}


/*
int32_t
p_part(int16_t error)
{
	return (pid.kp * error);
}

int32_t
i_part(int16_t error)
{
	if (time_now() > timing_var_i + TIME_CONSTANT)
	{
		timing_var_i = time_now();
		pid.integral_value = (int16_t)((pid.ti)*(pid.integral_value + error));
	}
	return pid.integral_value;
}

int32_t 
d_part(int16_t error)
{
	if (time_now() > timing_var_d + TIME_CONSTANT)
	{
		timing_var_d = time_now();
		pid.e_factor = (pid.td*(error - pid.e_factor));
	}
	return pid.e_factor;	
}
*/
