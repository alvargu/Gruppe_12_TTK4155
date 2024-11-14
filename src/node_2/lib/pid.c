
#include "pid.h"

// Define 
typedef struct {
	int8_t kp;
	int8_t ki;
	int8_t kd;
	int16_t integral_value;
	int8_t error_factor;
} PID;

// Instantiate pid struct for global values
PID pid;

// Initialize PID controller paramaters
void pid_init(int8_t kp, int8_t ki, int8_t kd) {
	pid.kp = kp;
	pid.ki = ki;
	pid.kd = kd;
	pid.integral_value = 0;
	pid.error_factor = 0;
}

int8_t pid_get_u(int8_t error)
{
     // Clamp integral influence
     if ((pid.integral_value < _IN) && (pid.integral_value))
}

