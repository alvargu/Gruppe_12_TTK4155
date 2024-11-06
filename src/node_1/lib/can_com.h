#ifndef CAN_COM_H
#define CAN_COM_H

#include <stdint.h>

typedef struct
{
		uint16_t id; //Standard identifier. Reminder: ID is 11 bits long (0 to 2047)
		uint8_t data_len; //Number of bytes to be transmitted (between 0 and 8)
		uint8_t data[8]; //At most 8 bytes of data to be transmitted.
} can_message_t;
 
//does all initialisation of SPI and MCP can controller
//(for now inits to loopback mode only)
void can_init(void);

//Transmits message over CAN
//Any value not = 0, 1, or 2 will probably produce unexpected errors.
void can_transmit(const can_message_t* p_message, uint8_t tx_buf /*for now just use 0 for this param */);

//can receive
#endif
