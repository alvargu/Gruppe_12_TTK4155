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

		can_message_t msg_received;

		//Menu to be displayed on OLED
		menu_t game_menu = 
		{ 9u, //length
		  6u, //active item
		  {
				  "|^--BOTTOM--^ |",
				  "| SECRET MENU |",
				  "| DEV OPTIONS |",
				  "|   HISTORY   |",
				  "|    INFO     |",
				  "| HIGH SCORE  |",
				  "|  PLAY GAME  |",
				  "|  SETTINGS   |",
				  "|  v--TOP--v  |"
		  }
		};

		oled_ui_draw_screen(&game_menu);

		uint8_t selection = 199u;

		uint8_t in_main_menu = 1u;
		uint8_t curr_score = 10;

		while (in_main_menu)
		{
				selection = oled_ui_handler(&game_menu);

				if (selection == 6)
				{
						oled_clear();
						oled_goto_pos(3,0);
						oled_printf("STARTING GAME", FONT_MEDIUM);
						oled_goto_pos(6,0);
						oled_printf("GOOD LUCK :)", FONT_MEDIUM);
						in_main_menu = 0;
				}
				else if(selection == 1)
				{
						oled_clear();
						oled_goto_pos(3,0);
						oled_printf("secret menu :D", FONT_MEDIUM);
				}
				else if (selection != 199)
				{
								oled_clear();
								oled_goto_pos(2,0);
								oled_printf("YOU HAVE SELECTED:", FONT_MEDIUM);
								oled_goto_pos(5,0);
								oled_printf(game_menu.menu_item[selection], FONT_MEDIUM);
								_delay_ms(1500);
				}
		_delay_ms(50);
		}

		_delay_ms(500);
		oled_clear();
		oled_goto_pos(4,0);
		oled_printf("   LOADING", FONT_MEDIUM);

		_delay_ms(50);
		oled_printf(".", FONT_MEDIUM);
		_delay_ms(100);
		oled_printf(".", FONT_MEDIUM);
		_delay_ms(20);
		oled_printf(".", FONT_MEDIUM);
		_delay_ms(150);
		oled_printf(".", FONT_MEDIUM);

		_delay_ms(200);
		oled_clear();
		oled_goto_pos(4,0);
		oled_printf("  GAME RUNNING!!", FONT_MEDIUM);

		while (1)
		{
				joystick_can_send();

				if (can_receive(&msg_received))
				{
						switch (msg_received.id)
						{
								case 11:
										printf("score dropped by one\n\r");
										curr_score--;
										printf("current score: %d\n\r", curr_score);
										break;
								default:
										;
						}
				}

				
		}
}

