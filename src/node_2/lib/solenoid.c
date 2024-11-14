
#include "solenoid.h"

#define SOLENOID_BOUNCE_DURATION msecs(100)  // 100  [ms]
#define _SOLENOID_PIN PIO_PC18

uint64_t start_timer_solenoid = 0;
bool bounce_state = 0;


// Initalization of solenoid enabling use of signal pin for solenoid
void solenoid_init(void) {
     // Enable power to PIO Port C via PMC
     PMC ->PMC_PCER0 |= PMC_PCER0_PID13;

     // Enable PIO control
     PIOC->PIO_PER |= _SOLENOID_PIN;
     // Set PIO to Output Enabled Mode
	PIOC->PIO_OER |= _SOLENOID_PIN;

	solenoid_off();
}


void solenoid_on(void) {
	// Set pin 45 LOW for on because it is driving a PNP transistor
	PIOC->PIO_CODR |= _SOLENOID_PIN;
}

void solenoid_off(void) {
	// Set pin 45 HIGH for off because it is driving a PNP transistor
	PIOC->PIO_SODR |= _SOLENOID_PIN;
}

// Used for timing of reset 
bool solenoid_extention_time_passed(void)
{
     return ((time_now() - start_timer_solenoid) > SOLENOID_BOUNCE_DURATION);
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
		start_timer_solenoid = time_now(); // Start timer
	}
	else if ((bounce_state == 1) && solenoid_extention_time_passed() {
		solenoid_off(); // OFF
	}
}
