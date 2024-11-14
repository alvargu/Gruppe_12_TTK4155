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

void main()
{
		printf("%c%c%c%c",0x1B,0x5B,0x32,0x4A); //clear screen

		//Inits that don't take much time:
		uart_init(MYUBRR);
		xmem_init();
		adc_init();
		oled_init();
		can_init();

		//Used for receiving messages from node2
		can_message_t msg_received;

		//Used for handshake, then whatever messages we might want to send
		can_message_t msg_send = {100u, 1u, {0xff, 0u, 0u, 0u, 0u, 0u, 0u, 0u}};

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


		oled_clear();
		oled_goto_pos(3,20);
		oled_printf("CALIBRATING", FONT_MEDIUM);
		oled_goto_pos(4,20);
		oled_printf("SYSTEM", FONT_MEDIUM);
		oled_goto_pos(6,20);
		oled_printf("PLEASE WAIT", FONT_MEDIUM);

		//This takes some time
		joystick_init_calibration();


		//Handshake stare of game with node2:
		bool node_2_handshake = 0;
		while (!(node_2_handshake))
		{
				can_transmit(&msg_send, 0);

				if (can_receive(&msg_received))
				{
						switch (msg_received.id)
						{
								case 100:
										node_2_handshake = 1;
										break;
								default:
										;
						}
				}
		}

		oled_clear();
		oled_goto_pos(4,20);
		oled_printf("CALIBRATION", FONT_MEDIUM);
		oled_goto_pos(5,20);
		oled_printf("COMPLETE", FONT_MEDIUM);
		_delay_ms(500);

		oled_clear();
		oled_ui_draw_screen(&game_menu);

		//Note: check for selection returns
		//199 if no selection has been made
		uint8_t selection = 199u;

		uint8_t in_main_menu = 1u;
		uint8_t curr_score = 15;
		char score_string[3];

		while (in_main_menu)
		{
				selection = oled_ui_handler(&game_menu);

				if (selection == 6)
				{
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
		oled_goto_pos(3,0);
		oled_printf("STARTING GAME", FONT_MEDIUM);
		oled_goto_pos(6,0);
		oled_printf("GOOD LUCK :)", FONT_MEDIUM);
		oled_clear();
		oled_goto_pos(6,0);
		oled_printf("GAME RUNNING!!", FONT_MEDIUM);

		while (curr_score > 0) //main event loop
		{
				joystick_can_send();


				if (can_receive(&msg_received))
				{
						switch (msg_received.id)
						{
								case 11:
										curr_score--;
										break;
								default:
										;
						}
				}
				//Convert score to string for
				//displaying on OLED
				itoa(curr_score, score_string, 10); 
				score_string[3] = '\0';

				oled_clear_line(4);
				oled_goto_pos(4, 10);
				oled_printf("Score is:  ", FONT_MEDIUM);
				oled_printf(score_string, FONT_MEDIUM);
		}

		oled_clear();
		oled_goto_pos(4, 10);
		oled_printf("GAME OVER :(", FONT_MEDIUM);

		while (1); //end of program
}

