#include "oled_ctrl.h"

static void 
write_command(uint8_t c)
{
    xmem_write(XMEM_OLED_COM, 0, c);
}

static void 
write_data(uint8_t d)
{
    xmem_write(XMEM_OLED_DATA, 0, d);
}

void 
oled_init()
{
    //Comments copied from datasheet
	write_command(0xae); //Display OFF
	write_command(0xa1); //column address 127 is mapped to SEG0
	write_command(0xda); //Alternative COM pin configuration and Disable COM Left/Right remap
	write_command(0x12); //Lower Page start adress
	write_command(0xc8); //remapped mode. Scan from COM[N-1] to COM0. Where N is the Multiplex ratio.
	write_command(0xa8); //Set multiplex ratio
	write_command(0x3f); //Set display RAM display start line register from 0-63 using X 5X 3X 2X 1X 0.
	write_command(0xd5); //Define the divide ratio (D) of the display clocks (DCLK): Divide ratio= A[3:0] + 1, RESET is 0000b (divide ratio = 1)
	write_command(0x80); //Set Contrast Control
	write_command(0x81); //Set Contrast Control
	write_command(0x50); //Set Display Start Line
	write_command(0xd9); //Set Pre-charge Period
	write_command(0x21); //Set Column Address 
	write_command(0x20); //Set Memory Addressing Mode
	write_command(0x00); //Set Lower Column Start Address for Page Addressing Mode
	write_command(0xdb); //Set V_COMH Deselect Level
	write_command(0x30); //Set Page Address
	write_command(0xad); //External or internal I_REF Selection
	write_command(0x00); //Set Lower Column Start Address for Page Addressing Mode
	write_command(0xa4); //Entire Display ON 
	write_command(0xa6); //Set Normal/Inverse Display
	write_command(0xaf); //Display ON

    //Horizontal Addressing mode
	write_command(0x20);
	write_command(0x00);

	oled_clear();
	
	write_command(0x20); //Set Memory Addressing Mode back to page mode
	write_command(0x02); 

}

void
oled_clear()
{
    //Clear Display
	for(int i = 0; i < 1024; i++){
		write_data(0x00);
	}

	oled_home();
}

//Function used to move the cursor to the top left corner
void
oled_home()
{
	write_command(0xB0);
	write_command(0x00);
	write_command(0x10);
}

void
oled_goto_line(uint8_t line)
{
	if(line < OLED_LINE_CNT && line >= 0)
	{
		write_command(0xB0 + line);
	}

	cursor_line = line;
}

void
oled_goto_column(uint8_t column)
{
	if(column < OLED_WIDTH && column >= 0)
	{
		write_command(0x00 |  (0x0f & column));
		write_command(0x10 | ((0xf0 & column) >> 4));

		cursor_column = column;
	}
}

void 
oled_clear_line(uint8_t line)
{
	//Move display "cursor" to the line
	oled_goto_line(line);
		
	//Iterate over display width and clear it
	for(uint8_t p = 0; p < OLED_WIDTH; p++)
	{
		write_data(0x00);
	}	
}

void 
oled_clear_column(uint8_t column)
{
	oled_goto_column(column);
	//Clear Column
	write_data(0x00);
}

void
oled_pos(uint8_t line, uint8_t column)
{
	oled_goto_line(line);
	oled_goto_column(column);
}

//Function assumes the "cursor" has been placed at string start
void
oled_print_string(char* str, uint8_t font_size)
{
	uint8_t str_itr = 0x00;
	
	while(str_itr < str_size)
	{
		write_data(pgm_read_byte(str[*(str + str_itr) - 32][str_itr]));
		str_itr++;
	}
}

uint8_t
oled_get_cursor()
{
	return cursor_line;
}