#include "sam.h"
#include <stdio.h>

#include "lib/ir_driver.h"
#include "lib/uart.h"
#include "lib/can.h"
#include "lib/pwm_ctrl.h"

#define F_CPU 84000000
#define BAUD 9600

CanInit bit_timing = {.phase2 = 5, .propag = 1, .phase1 = 6, .sjw = 0, .brp = 41, .smp = 0};

int 
main(void)
{
    SystemInit();
	WDT -> WDT_MR |= WDT_MR_WDDIS;
	
	uart_init(F_CPU,BAUD);
	adc_init();
	pwm_init();
	can_init(bit_timing, 0);
	
	CanMsg recive_msg;

	printf("Game Started!\n\r");
    while(1) 
    {
		while(!(can_rx(&recive_msg)))
		{
			;
		}
		pwm_update_duty_cycle(pwm_scale(recive_msg.byte[0]));
		if(is_goal()){
			printf("GOAL!!!\n\r");	
		}
    }
}
