#include "pid.h"

// Instantiate pid struct for global values
PID pid;

// Initialize PID controller parameters
void pid_init(int8_t kp, int8_t ti, int8_t td) {
	pid.kp = kp;
	pid.ti = ti;
	pid.td = td;
	pid.e_factor = 0;
	pid.integral_value = 0;
}

int8_t pid_get_u(int8_t error)
{
	// Clamp integral influence
	//if ((pid.integral_value < INTEGER CLAMPS) && (pid.integral_value))
}

uint8_t
p_part(uint8_t error)
{
	return (pid.kp * error);
}

uint8_t
i_part(uint8_t error)
{
	return (pid.integral_value + error);
}

uint8_t 
d_part(uint8_t error)
{
	return (error - pid.e_factor);	
}

uint16_t
integrator(uint8_t error)
{
	return p_part(error) + i_part(error) + d_part(error);
}