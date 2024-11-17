#include "pwm_ctrl.h"

void
pwm_init(void)
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
	PWM -> PWM_CH_NUM[1].PWM_CDTY = PWM_MS/PWM_FRQ/2;				//Centers the servo
																							
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
	//Main "command" used to load the update registers to main PWM registers
	PWM -> PWM_SCUC					       |= PWM_SCUC_UPDULOCK;
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
	return (x_val*max_val/JOYSTICK_VAL_RANGE) + PWM_MIN;
}

void
pwm_motor_init(void)
{
	PMC -> PMC_PCER1				|= PMC_PCER1_PID36;		//Enable Peripheral in PMC
	
	PIOB -> PIO_ABSR				|= PIO_PB12;			//Set Pin PB12 to be controlled by PWM
	PIOB -> PIO_PDR					|= PIO_PB12;			//Disable control of the pin by PIO
	
	PWM -> PWM_CLK					|= PWM_CLK_DIVA(1);		//Enable CLK Divider A
	PWM -> PWM_CLK					|= PWM_CLK_PREA(0b1010);//Configure DivA as MCK/1024
	
	PWM -> PWM_SCM					|= PWM_SCM_SYNC0		//Configure Channel 0 as non synchronous
									|  PWM_SCM_UPDM_MODE0;	//Manual control of update channels and update registers
						
	PWM -> PWM_CH_NUM[0].PWM_CMR	|= PWM_CMR_CPRE_CLKA	//Connect Channel 0 to CLK A
									|  PWM_CMR_CPOL;		//Invert PWM output meaning duty cycle is high
									
	PWM -> PWM_CH_NUM[0].PWM_CPRD	 = PWM_MOTOR_PER;		//Assign Period Value
	PWM -> PWM_CH_NUM[0].PWM_CDTY	 = 0;					//0% Duty Cycle for init
	
	PWM -> PWM_ENA					 = PWM_ENA_CHID0;		//Enable PWM on channel 0
}

void
pwm_set_motor_speed(uint16_t dc_val)
{
	if(dc_val >= 0 && dc_val <= PWM_MOTOR_PER)
	{
		PWM -> PWM_CH_NUM[0].PWM_CDTY = dc_val;
	}
	else if(dc_val > PWM_MOTOR_PER)
	{
		PWM -> PWM_CH_NUM[0].PWM_CDTY = PWM_MOTOR_PER;
	}
	else if(dc_val < 0)
	{
		PWM -> PWM_CH_NUM[0].PWM_CDTY = 0;
	}
}