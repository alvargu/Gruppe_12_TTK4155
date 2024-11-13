#include "oled_ui.h"

#define F_CPU 4915200 //Clock Speed
#include <util/delay.h>

void oled_ui_draw_screen(menu_t* const menu)
{
		uint8_t above_item;
		uint8_t below_item;
		uint8_t length = menu -> menu_length;
		uint8_t active = menu -> active_item;

		if (active == 0)
		{
				above_item = 1;
				below_item = length - 1;
		}
		else if (active == (length - 1))
		{
				above_item = 0;
				below_item = active - 1;
		}
		else
		{
				above_item = active + 1;
				below_item = active -1;
		}

		oled_clear();

		oled_goto_pos(0,0);
		oled_printf("   |             |   ", FONT_MEDIUM);
		oled_goto_pos(1,0);
		oled_printf("   |             |   ", FONT_MEDIUM);
		oled_goto_pos(3,0);
		oled_printf("   |             |   ", FONT_MEDIUM);
		oled_goto_pos(5,0);
		oled_printf("   |             |   ", FONT_MEDIUM);
		oled_goto_pos(7,0);
		oled_printf("   |             |   ", FONT_MEDIUM);

		oled_goto_pos(2,0);
		oled_printf("   ", FONT_MEDIUM);
		oled_printf(((menu -> menu_item)[above_item]), FONT_MEDIUM);

		oled_goto_pos(4,0);
		oled_printf(" > ", FONT_MEDIUM);
		oled_printf(((menu -> menu_item)[active]), FONT_MEDIUM);
		oled_printf(" < ", FONT_MEDIUM);

		oled_goto_pos(6,0);
		oled_printf("   ", FONT_MEDIUM);
		oled_printf(((menu -> menu_item)[below_item]), FONT_MEDIUM);
}

void oled_ui_update_active(menu_t* menu, joystick_direction_t direction)
{
		uint8_t active = menu -> active_item;
		uint8_t length = menu -> menu_length;
		switch (direction)
		{
				case up:
						if (active == (length - 1))
						{
								(menu -> active_item) = 0;
						}
						else
						{
								(menu -> active_item) = active + 1;
						}
						break;
				case down:
						if (active == 0)
						{
								(menu -> active_item) = length - 1;
						}
						else
						{
								(menu -> active_item) = active - 1;
						}
						break;
				default:
						;
						//do nothing
		}

}

uint8_t oled_ui_select_item(menu_t* const menu)
{
		//Button pressed corresponds to "logic low" on pin 4
		if (!((PIND >> PD4) & 0x1))
		{
				return menu -> active_item;
		}
		return 199;
}

uint8_t oled_ui_handler(menu_t* menu)
{

		raw_adc_data_t adc_readout;
		joystick_direction_t direction;

		adc_sample(&adc_readout);
		direction = joystick_get_direction(&adc_readout);

		if (direction != neutral)
		{
				_delay_ms(300);
				adc_sample(&adc_readout);
				direction = joystick_get_direction(&adc_readout);

				if (direction != neutral)
				{
						oled_ui_update_active(menu, direction);
						oled_ui_draw_screen(menu);
				}
		}

		return oled_ui_select_item(menu);
}

