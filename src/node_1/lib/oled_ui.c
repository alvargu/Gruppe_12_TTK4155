#include "oled_ui.h"

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
		oled_goto_pos(2,0);
		oled_printf(((menu -> menu_item)[above_item]), FONT_MEDIUM);

		oled_goto_pos(4,0);
		oled_printf(" > ", FONT_MEDIUM);
		oled_printf(((menu -> menu_item)[active]), FONT_MEDIUM);
		oled_printf(" < ", FONT_MEDIUM);

		oled_goto_pos(6,0);
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

