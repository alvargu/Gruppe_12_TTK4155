#include "oled_ctrl.h"

void 
oled_init()
{
    //Comments copied from datasheet
	sram_write(SRAM_OLED_COM, 0, 0xae); //Display OFF
	sram_write(SRAM_OLED_COM, 0, 0xa1); //column address 127 is mapped to SEG0
	sram_write(SRAM_OLED_COM, 0, 0xda); //Alternative COM pin configuration and Disable COM Left/Right remap
	sram_write(SRAM_OLED_COM, 0, 0x12); //Lower Page start adress
	sram_write(SRAM_OLED_COM, 0, 0xc8); //remapped mode. Scan from COM[N-1] to COM0. Where N is the Multiplex ratio.
	sram_write(SRAM_OLED_COM, 0, 0xa8); //Set multiplex ratio
	sram_write(SRAM_OLED_COM, 0, 0x3f); //Set display RAM display start line register from 0-63 using X 5X 3X 2X 1X 0.
	sram_write(SRAM_OLED_COM, 0, 0xd5); //Define the divide ratio (D) of the display clocks (DCLK): Divide ratio= A[3:0] + 1, RESET is 0000b (divide ratio = 1)
	sram_write(SRAM_OLED_COM, 0, 0x80); //Set Contrast Control
	sram_write(SRAM_OLED_COM, 0, 0x81); //Set Contrast Control
	sram_write(SRAM_OLED_COM, 0, 0x50); //Set Display Start Line
	sram_write(SRAM_OLED_COM, 0, 0xd9); //Set Pre-charge Period
	sram_write(SRAM_OLED_COM, 0, 0x21); //Set Column Address 
	sram_write(SRAM_OLED_COM, 0, 0x20); //Set Memory Addressing Mode
	sram_write(SRAM_OLED_COM, 0, 0x00); //Set Lower Column Start Address for Page Addressing Mode
	sram_write(SRAM_OLED_COM, 0, 0xdb); //Set V_COMH Deselect Level
	sram_write(SRAM_OLED_COM, 0, 0x30); //Set Page Address
	sram_write(SRAM_OLED_COM, 0, 0xad); //External or internal I_REF Selection
	sram_write(SRAM_OLED_COM, 0, 0x00); //Set Lower Column Start Address for Page Addressing Mode
	sram_write(SRAM_OLED_COM, 0, 0xa4); //Entire Display ON 
	sram_write(SRAM_OLED_COM, 0, 0xa6); //Set Normal/Inverse Display
	sram_write(SRAM_OLED_COM, 0, 0xaf); //Display ON

    //Horizontal Addressing mode
	sram_write(SRAM_OLED_COM, 0, 0x20);
	sram_write(SRAM_OLED_COM, 0, 0x00);

	//Clear Display
	for(int i = 0; i < 1024; i++){
		sram_write(SRAM_OLED_DATA, 0, 0x00);
	}
	
	sram_write(SRAM_OLED_COM, 0, 0x20); //Set Memory Addressing Mode back to page mode
	sram_write(SRAM_OLED_COM, 0, 0x02); 
	
	sram_write(SRAM_OLED_COM, 0, 0xB3);
	sram_write(SRAM_OLED_COM, 0, 0x05);			//f0
	sram_write(SRAM_OLED_COM, 0, 0x14);
	sram_write(SRAM_OLED_DATA, 0, 0b00011000);
	sram_write(SRAM_OLED_DATA, 0, 0b00011000);
	sram_write(SRAM_OLED_DATA, 0, 0b00011000);
	sram_write(SRAM_OLED_DATA, 0, 0b00011000);
	sram_write(SRAM_OLED_DATA, 0, 0b00011000);
	sram_write(SRAM_OLED_DATA, 0, 0b00011000);
	sram_write(SRAM_OLED_DATA, 0, 0b00011000);
	sram_write(SRAM_OLED_DATA, 0, 0b00011000);
	sram_write(SRAM_OLED_DATA, 0, 0b00011000);
	sram_write(SRAM_OLED_DATA, 0, 0b00011000);
	sram_write(SRAM_OLED_DATA, 0, 0b11111111);
	sram_write(SRAM_OLED_DATA, 0, 0b01111110);
	sram_write(SRAM_OLED_DATA, 0, 0b00111100);
	sram_write(SRAM_OLED_DATA, 0, 0b00011000);
}

void
oled_printf(uint8_t* oled_string)
{



}
