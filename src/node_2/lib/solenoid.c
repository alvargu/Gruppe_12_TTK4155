
#include "solenoid.h"

#define SOLENOID_BOUNCE_DURATION msecs(100)  // 100  [ms]
#define _SOLENOID_PIN PIO_PC18

uint64_t start_timer_solenoid = 0;
bool bounce_state = 0;


// Initalization of solenoid enabling use of signal pin for solenoid
void solenoid_init() {
    // Enable power to PIO Port C via PMC
    PMC ->PMC_PCER0 |= PMC_PCER0_PID13;

    // Enable PIO control
    PIOC->PIO_PER |= PIO_PC18;
    // Set PIO to Output Enabled Mode
	PIOC->PIO_OER |= PIO_PC18;

	solenoid_off();	//Clear Pin and make sure its set to LOW 
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
    if ((punch == 1) && (bounce_state == 0)) {
		solenoid_on(); // ON
		bounce_state = 1; // Lock
		start_timer_solenoid = time_now(); // Start timer
	}
	// Reset timing for solenoid
	if ((bounce_state == 1) && solenoid_lock_time_passed()) {
		bounce_state = 0;
	}
	else if ((bounce_state == 1) && solenoid_bounce_time_passed()) {
		solenoid_off(); // OFF
	}
}
