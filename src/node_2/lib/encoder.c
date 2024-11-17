
#include "encoder.h"

// PC25 = ChA (D4)
// PC26 = ChB (D5)
#define _ENCODER_A_PIN PIO_PC26
#define _ENCODER_B_PIN PIO_PC25

#define _ENCODER_STEP_MAX 1400 

// value used to store current encoder position
volatile int32_t encoder_steps = 0;
volatile uint8_t state = 0;

void encoder_init(void)
{
    // Activate power to TC0
    PMC -> PMC_PCER0 |= PMC_PCER0_PID13 | PMC_PCER0_PID11;
     
    // Enable channel A pin as input
    PIOC -> PIO_PER |= _ENCODER_A_PIN;
    PIOC -> PIO_ODR |= _ENCODER_A_PIN;
    // Enable channel B pin as input
    PIOC -> PIO_PER |= _ENCODER_B_PIN;
    PIOC -> PIO_ODR |= _ENCODER_B_PIN;

    // Additional mode for Channel A sett to Rising Edge Detection for Channel A
    PIOC -> PIO_AIMER  |= _ENCODER_A_PIN;
	PIOC -> PIO_REHLSR |= _ENCODER_A_PIN;
	
    // Enable interrupt for Encoder Pin Channel A
    PIOC -> PIO_IER = _ENCODER_A_PIN;

    // Enable interrupt handling on Encoder Pin Channel A
    NVIC_EnableIRQ(PIOC_IRQn);
}

int32_t encoder_get_pos(void)
{
	return encoder_steps;
}

// Used to reset position value to zero when calibrating setup
void encoder_pos_rst(void)
{
     encoder_steps = 0;
}

void PIOC_Handler(void) {
	// Check if interrupt is from Encoder Channel A
	if (PIOC->PIO_ISR & _ENCODER_A_PIN) {
		state = (PIOC -> PIO_PDSR & _ENCODER_B_PIN) ? 1 : 0;
		if(state == 0){
			encoder_steps++;
		}else if(state == 1){
			encoder_steps--;
		}
				
		//Clear pending interrupt
		NVIC_ClearPendingIRQ(PIOC_IRQn);
	}
}


