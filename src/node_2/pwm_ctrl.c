#include "pwm_ctrl.h"

void
pwm_init()
{
	PMC -> PMC_PCER1	|= PMC_PCER1_PID36;				//Enable Peripheral in PMC
	
	PIOB -> PIO_ABSR	|= PIO_PB13;					//Set Pin PB13 to be controlled by PWM
	PIOB -> PIO_PDR		|= PIO_PB13;					//Disable control of the pin by PIO
	
										//Clock Config
	PWM -> PWM_CLK		|= PWM_CLK_DIVB(1);				//Enable CLK Divider B
	PWM -> PWM_CLK		|= PWM_CLK_PREB(0b1001);			//Configure DivB as MCK/512
												
	PWM -> PWM_SCM		|= PWM_SCM_SYNC0				//Configure Channel 1 as non synchronous
				|  PWM_SCM_UPDM_MODE0;				//Manual control of update channels and update registers
																	
	PWM -> PWM_CH_NUM[1].PWM_CMR	|= PWM_CMR_CPRE_CLKB			//Connect Channel 1 to CLK B
					|  PWM_CMR_CPOL;			//Invert PWM output meaning duty cycle is high
	PWM -> PWM_CH_NUM[1].PWM_CPRD = PWM_MS/PWM_FRQ;				//Asign Period Value (~3_280)
	PWM -> PWM_CH_NUM[1].PWM_CDTY = PWM_CENTER;				//Centers the servo
																							
	PWM -> PWM_ENA		= PWM_ENA_CHID1;				//Enable PWM on channel 1
}

//Check if the input value is within bounds and if so load it to the register
void
pwm_update_duty_cycle(uint16_t dc_val)
{	
	if(dc_val <= PWM_MAX && dc_val >= PWM_MIN)
	{
		PWM -> PWM_CH_NUM[1].PWM_CDTYUPD		= dc_val;		
	} 
	else if(dc_val >= PWM_MAX)
	{
		PWM -> PWM_CH_NUM[1].PWM_CDTYUPD		= PWM_MAX;
	}
	else if(dc_val <= PWM_MIN){
		PWM -> PWM_CH_NUM[1].PWM_CDTYUPD		= PWM_MIN;
			
	}
	PWM -> PWM_SCUC					       |= PWM_SCUC_UPDULOCK;	//Main "command" used to load the update registers to main PWM registers
}

void
pwm_update_period_value(uint16_t per_val)
{
	PWM -> PWM_CH_NUM[1].PWM_CPRDUPD		= per_val;
	PWM -> PWM_SCUC						   |= PWM_SCUC_UPDULOCK;
}

void
pwm_update_dead_time(uint16_t dead_time_val)
{
	PWM -> PWM_CH_NUM[1].PWM_DTUPD			= dead_time_val;
	PWM -> PWM_SCUC						   |= PWM_SCUC_UPDULOCK;
}

//Scale the input value to one within bounds
//Its dependent on the fact that x_val is always in range of 0-200
uint16_t
pwm_scale(uint16_t x_val)
{
	uint16_t max_val = PWM_MAX - PWM_MIN;
	return CAN_MSG_RANGE - (x_val*max_val/CAN_MSG_RANGE) + PWM_MIN;
}
