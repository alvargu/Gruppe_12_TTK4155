#include "can_ctrl.h"
#include "spi.h"
#include "mcp2515.h"

#define F_CPU 4915200 //Clock Speed
#include <util/delay.h>

#define RESET 				0b11000000
#define READ 				0b00000011
#define WRITE 				0b00000010
#define REQUEST_TO_SEND 		0b10000000
#define READ_STATUS 		0b10100000
#define BIT_MODIFY 			0b00000101

void can_ctrl_request_send(uint8_t transmit_buffer)
{
		uint8_t command_byte = REQUEST_TO_SEND + (0b00000111 & transmit_buffer);

		spi_open_channel();
		spi_tx(command_byte);
		spi_close_channel();
}

uint8_t can_ctr_read_status(void)
{
		uint8_t received;
		spi_open_channel();
		spi_tx(READ_STATUS); 
		received = spi_rx();
		spi_close_channel();
		return received;
}

void can_ctrl_write(uint8_t reg_adress, uint8_t data)
{
		spi_open_channel();
		spi_tx(MCP_WRITE);
		spi_tx(reg_adress);
		spi_tx(data);
		spi_close_channel();
}

void can_ctrl_bit_modify(uint8_t reg_adress, uint8_t mask, uint8_t data)
{
		spi_open_channel();
		spi_tx(BIT_MODIFY);
		spi_tx(reg_adress);
		spi_tx(mask);
		spi_tx(data);
		spi_close_channel();
}

uint8_t can_ctrl_read(uint8_t reg_adress)
{
		uint8_t received;
		spi_open_channel();
		spi_tx(MCP_READ);
		spi_tx(reg_adress);
		received = spi_rx();
		spi_close_channel();
		return received;
}

void can_ctrl_reset(void)
{
		spi_open_channel();
		spi_tx(MCP_RESET);
		spi_close_channel();
		_delay_ms(10);
}
