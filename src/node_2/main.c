#include "sam.h"
#include <stdio.h>

#include "lib/ir_driver.h"
#include "lib/uart.h"
#include "lib/can.h"
#include "lib/pwm_ctrl.h"
#include "lib/solenoid.h"
#include "lib/encoder.h"
#include "lib/motor.h"
#include "lib/pid.h"

#define F_CPU	84000000
#define BAUD		9600

#define RANGE	1400
#define CENTER   700
#define POINT	   7

CanInit can_bit_timing = {.phase2 = 5, .propag = 1, .phase1 = 6, .sjw = 0, .brp = 41, .smp = 0};

int
main(void)
{
	SystemInit();
	WDT -> WDT_MR |= WDT_MR_WDDIS;
	
	uart_init(F_CPU,BAUD);
	adc_init();
	pwm_init();
	can_init(can_bit_timing, 0);
	solenoid_init();
	encoder_init();
	motor_init();
	
	CanMsg recive_msg;
	CanMsg send_msg;
	
	//For the control system:
	volatile uint16_t pos_reference = 0;
	volatile int16_t current_position = 0;
	volatile int16_t plant_input = 0;
	volatile int16_t error;

	
	//These values gives a PI that feels good,
	//but still gets a bit stuck at low speeds.
	pid_init(0.5,2,0);			
	
	motor_return_to_zero();
	encoder_pos_rst();
	
	printf("calibration done\n\r");
	printf("Encoder position: %ld\n\r", encoder_get_pos());
	
	printf("Waiting for handshake\n\r");

	
	//Handshake with node1
	while(1){
		if(can_rx(&recive_msg))
		{
			if(recive_msg.id == 100) //Init/handshake msgid
			{
				send_msg.id = 100;
				send_msg.length = 1;
				send_msg.byte[0] = 0xFF;
				can_tx(send_msg);
				break;
			} 
		}
	}
		
	
	//Small delay after accepting handshake
	uint64_t tim = time_now();
	while(time_now() < (tim + msecs(400)))
	;


restart_from_node1:		
	printf("Game Started!\n\r");
	
	while(1) //main event loop
	{
		
		while(1)
		{
			if(can_rx(&recive_msg))
			{
				if(recive_msg.id == 100) //Init/handshake msgid
				{
					send_msg.id = 100;
					send_msg.length = 1;
					send_msg.byte[0] = 0xFF;
					can_tx(send_msg);
					printf("jumping!\n\r");
					goto restart_from_node1;
				}
				else
				{
					break;	
				}
				
			}
			
			//printf("waiting for joystick data\n\r");
			motor_speed_set(0);
		}
		
		
		//Control carriage position
		pos_reference = recive_msg.byte[0] * POINT;
		current_position = encoder_get_pos();
		error = (pos_reference - current_position); //sampled error
		plant_input = pid_get_u(error);  //sampled error -> u		
		motor_speed_set(plant_input);
		
		//Removing this print makes the motor/PI controller not work
		printf("Error: %d | plant_input: %d | POS: %d | reference: %d |\n\r", error, plant_input,current_position, pos_reference);
		
		
		//Set servo angle
		pwm_update_duty_cycle(pwm_scale(recive_msg.byte[1])); 
		
		//Register and send back info about goals
		if(is_goal()){
			printf("GOAL!!!\n\r");
			send_msg.id = 11;
			send_msg.length = 1;
			send_msg.byte[0] = 0xFF;
			can_tx(send_msg);
		}
		
		
		//Punch solenoid.
		
		
		if(recive_msg.byte[2])
		{
			solenoid_punch(1);
			printf("PUNCH!\n\r");
		}
		else
		{
			solenoid_punch(0);
		}
		
		//Small delay is needed for motor to work
		tim = time_now();
		while(time_now() < (tim + usecs(200)))
		;
		
			
	}
}
