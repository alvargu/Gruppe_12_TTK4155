
#include "solenoid.h"

uint64_t start_time_solenoid = 0;
bool bounce_state = 0;


// Initalization of solenoid enabling use of signal pin for solenoid
void solenoid_init() {
     // Enable power to PIO Port C via PMC
     PMC ->PMC_PCER0 |= PMC_PCER0_PID13;

     // Enable PIO control
     PIOC->PIO_PER |= PIO_PC18;
     // Set PIO to Output Enabled Mode
	PIOC->PIO_OER |= PIO_PC18;
}


void solenoid_on() {
	// Set pin 45 HIGH
	PIOC->PIO_SODR |= PIO_PC18;
}

void solenoid_off() {
	// Set pin 45 LOW
	PIOC->PIO_CODR |= PIO_PC18;
}

// Used for timing of reset 
bool solenoid_extention_time_passed(void)
{
     return ((time_now() - start_time_solenoid) > SOLENOID_BOUNCE_DURATION);
}

void solenoid_punch(bool punch) {
     // unsure if this part is needed
     //if ((punch == 0) && (bounce_state == 0)) {
	//	solenoid_off(); // OFF
	//	bounce_state = 0; // Reset
	//}

	//replace if with else if when adding part over
     if ((punch == 1) && (bounce_state == 0)) {
		solenoid_on(); // ON
		bounce_state = 1; // Lock
		start_time_solenoid = time_now(); // Start timer
	}
	else if ((bounce_state == 1) && solenoid_extention_time_passed() {
		solenoid_off(); // OFF
	}
}
