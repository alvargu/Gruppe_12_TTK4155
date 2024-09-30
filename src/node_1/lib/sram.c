#include "xmem.h"

bool
xmem_init()
{
	MCUCR = 0b10000000;
	SFIOR = (1 << XMM2);

	volatile char* ext_ram = (char*) XMEM_MEM;
	uint16_t ext_ram_size = 0x800;
	uint16_t write_error = 0; 
	uint16_t retrival_errors = 0;
	uint16_t seed = rand();

	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++)
	{
		uint8_t s_val = rand();
		ext_ram[i] = s_val;

		uint8_t ret_val = ext_ram[i];
		if(s_val != ret_val){
			write_error++;
		}
	
	}

	srand(seed);
	for(uint16_t i = 0; i < ext_ram_size; i++){
		uint8_t s_val   = rand();
		uint8_t ret_val = ext_ram[i];

		if(s_val != ret_val){
			retrival_errors++;
		}
	}

	return !(write_error + retrival_errors);
}

void 
xmem_write(uint16_t mem_loc, uint8_t adrr, uint8_t val)
{	
	volatile char* ext_ram = (char*) mem_loc;
	ext_ram[adrr] = (char*)val;
}

uint8_t 
xmem_read(uint16_t mem_loc,uint8_t adrr)
{
	volatile char* ext_ram = (char*) mem_loc;
	return ext_ram[adrr];;
}