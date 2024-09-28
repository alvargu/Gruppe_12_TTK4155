#include "sram.h"

bool
sram_init()
{
	volatile char* ext_ram = (char*) SRAM_MEM;
	uint16_t ext_ram_size = 0x800;
	uint16_t write_error = 0; 
	uint16_t retrival_errors = 0;
	printf("SRAM Test...\n");

	MCUCR = 0b10000000;
	SFIOR = (1 << XMM2);

	uint16_t seed = rand();

	srand(seed);

	for (uint16_t i = 0; i < ext_ram_size; i++)
	{
		uint8_t s_val = rand();
		ext_ram[i] = s_val;

		uint8_t ret_val = ext_ram[i];
		if(s_val != ret_val){
			printf("Write Error at %4d = %02x (expected %02x)\n", i, ret_val, s_val);
			write_error++;
		}
	
	}

	srand(seed);
	for(uint16_t i = 0; i < ext_ram_size; i++){
		uint8_t s_val   = rand();
		uint8_t ret_val = ext_ram[i];

		if(s_val != ret_val){
			printf("Retrival error at %4f = %02x (expected %02x)\n", i, ret_val, s_val);
			retrival_errors++;
		}
	}

	printf("SRAM Test Done, Got %4d Write Errors and %4d Retrival Errors.\n", write_error, retrival_errors);

	return !(write_error + retrival_errors);
}

//
//
//
void 
sram_write(uint16_t mem_loc, uint8_t adrr, uint8_t val)
{	
	volatile char* ext_ram = (char*) mem_loc;
	ext_ram[adrr] = (char*)val;
	free(ext_ram);
}

//
//
//
uint8_t 
sram_read(uint16_t mem_loc,uint8_t adrr)
{
	volatile char* ext_ram = (char*) mem_loc;
	uint8_t output = ext_ram[adrr]; 
	free(ext_ram);
	return output;
}