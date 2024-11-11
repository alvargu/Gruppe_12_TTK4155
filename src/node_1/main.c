#include <avr/io.h>
#include "lib/uart_com.h"
#include "lib/xmem.h"
#include <stdio.h>
#include <stdlib.h>
#include "lib/ADC_Driver.h"
#include "lib/can_com.h"
#include "lib/spi.h"
#include "lib/can_ctrl.h"
#include "lib/mcp2515.h"
#include "lib/joystick.h"
#include "lib/oled_ctrl.h"
#include "lib/oled_ui.h"


#define F_CPU 4915200 //Clock Speed
#include <util/delay.h>

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1


static int x;

static void func(){
}

void main()
{
		printf("%c%c%c%c",0x1B,0x5B,0x32,0x4A); //clear screen
		uart_init(MYUBRR);
		xmem_init();
		adc_init();
		joystick_init_calibration();
		oled_init();
		can_init();

		menu_t game_menu = 
		{ 6u, //length
		  2u, //active item
		  {
				  "SETTINGS",
				  "PLAY GAME",
				  "HIGH SCORES",
				  "HISTORY",
				  "BRUH",
				  "TEST"
		  }
		};

		oled_ui_draw_screen(&game_menu);


		raw_adc_data_t adc_readout;
		joystick_direction_t direction;

		
		while (1)
		{
				adc_sample(&adc_readout);
				direction = joystick_get_direction(&adc_readout);

				oled_ui_update_active(&game_menu, direction);
				oled_ui_draw_screen(&game_menu);
				_delay_ms(100);
		}
		
}
