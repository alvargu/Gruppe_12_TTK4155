#include "oled_ctrl.h"
#include "joystick.h"
#include "oled_ctrl.h"
#include "ADC_Driver.h"


#ifndef OLED_UI_H
#define OLED_UI_H

//max number of chars with medium font size
#define MAX_CHARS 16 
#define MAX_MENU_LENGTH 16

typedef struct{
		uint8_t menu_length; //number of strings in menu
		uint8_t active_item;
		char menu_item[MAX_MENU_LENGTH][MAX_CHARS];
} menu_t;

void oled_ui_update_active(menu_t* menu, joystick_direction_t direction);

void oled_ui_draw_screen(menu_t* const menu);

uint8_t oled_ui_select_item(menu_t* const menu, /* something to detect joystick button*/);

#endif
