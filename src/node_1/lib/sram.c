#include "sram.h"

bool sram_check(){
    volatile char* ext_ram = (char*) SRAM_MEM;
    uint16_t ext_ram_size = 0x800;
    uint16_t write_error, retrival_errors = 0;
    printf("SRAM Test...\n");

    uint16_t seed = rand();

    srand(seed);

    for (uint16_t i = 0; i < ext_ram_size; i++)
    {
        uint8_t s_val = rand();
        ext_ram[i] = s_val;

        uint8_t ret_val = ext_ram[i];
        if(s_val != ret_val){
            printf("Write Error at ext_ram[%4d] = %02x (expected %02x)\n", i, ret_val, s_val);
            write_error++;
        }
    }

    srand(seed);
    for(uint16_t i = 0; i < ext_ram_size; i++){
        uint8_t s_val   = rand();
        uint8_t ret_val = ext_ram[i];

        if(s_val != ret_val){
            printf("Retrival error at ext_ram[%4f] = %02x (expected %02x)\n", i, ret_val, s_val);
            retrival_errors++;
        }
    }

    printf("SRAM Test Done, Got %4d Write Errors and %4d Retrival Errors.\n", write_error, retrival_errors);

    return !(write_error + retrival_errors);
}