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

uint8_t oled_ui_handler(menu_t* menu);

//Updates the active menu item based on joystick direction.
void oled_ui_update_active(menu_t* menu, joystick_direction_t direction);

//Draws screen according to menu. (active item in the middle of the screen, 
//with the correct items above and below.
void oled_ui_draw_screen(menu_t* const menu);

//Checks if joystick button is pressed, if it is, returns index of the current active menu item.
uint8_t oled_ui_select_item(menu_t* const menu);
#endif
