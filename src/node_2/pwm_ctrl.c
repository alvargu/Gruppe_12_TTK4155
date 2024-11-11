#include "pwm_ctrl.h"

void
pwm_init()
{
		PMC -> PMC_PCER1 |= PMC_PCER1_PID36;
	
	//PIOB -> PIO_PER		|= PIO_PB13;			//Enable pin PB13 as output
												//PWM is going to output on said pin
	PIOB -> PIO_ABSR	|= PIO_PB13;
	PIOB -> PIO_PDR		|= PIO_PB13;
	
												//Clock Config
	PWM -> PWM_CLK		|= PWM_CLK_DIVB(100);	//Enable CLK Divider B
												//Assumed that is is used for PWMH
	
	PWM -> PWM_CLK		|= PWM_CLK_PREB(5);		//Configure Pre-scaler as MCK/32
												//Later on divide it by value of the prescaler
												//meaning that the final freq is MCK/32/100
														
	PWM -> PWM_SCM		 = PWM_SCM_SYNC1		//Configure Channel 1 as synchronous
						|  PWM_SCM_UPDM_MODE0;	//Manual control of update channels and update registers
												//Now its possible to use UPD registers instead of direct registers
																	
	PWM -> PWM_CH_NUM[1].PWM_CMR = PWM_CMR_CPRE_CLKB;
	PWM -> PWM_CH_NUM[1].PWM_CPRD = 2625;
	PWM -> PWM_CH_NUM[1].PWM_CDTY = 1312;
																							
	PWM -> PWM_ENA		= PWM_ENA_CHID1;		//Enable PWM on channel 1
}

void
pwm_udc(uint16_t dc_val)
{
	//Get val of period an multiply it by percentage
	uint16_t got_val = 10;
	uint16_t val = got_val*dc_val/100;
	if(val > PWM_MIN && val < PWM_MAX){
		PWM -> PWM_CH_NUM[3].PWM_CDTYUPD = dc_val;
	}
}

void
pwm_upv(uint16_t per_val)
{
	PWM -> PWM_CH_NUM[3].PWM_CPRDUPD	 = per_val;
}

void
pwm_udt(uint16_t dead_time_val)
{
	PWM -> PWM_CH_NUM[3].PWM_DTUPD	     = dead_time_val;
}

void
pwm_apply_timings()
{
	PWM -> PWM_SCUC		|= PWM_SCUC_UPDULOCK;
}

void
default_values()
{
	pwm_upv(10000);			//Max Value
	pwm_udc(200);			//Range 90 - 210
	pwm_udt(0);				//No idea what it does for now
	pwm_apply_timings();	//Apply changes
}
