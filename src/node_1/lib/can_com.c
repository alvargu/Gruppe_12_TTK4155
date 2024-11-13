#include "can_com.h"
#include "can_ctrl.h"
#include "mcp2515.h"
#include "spi.h"
#include <stdio.h>

//#define LOOPBACK_TEST //undefine when not testing in loopback mode

#define TXRTSCTRL 0x0Du
#define FULL_REG_MASK 0xFFu

//Transmit buffers. Offset by 0x10 and 0x20 to get to buffer 1 and 2

//Standard ID high bits (bit 7-0 => ID bit 10-3)
#define TX_ID_HIGH 0x31u

//Standard ID low bits (REMINDER: only bit 7-5 is used, corresponds
//to ID bit 2-0)
#define TX_ID_LOW 0x32u

//Data length
#define TX_DATA_LEN 0x35u

//Data bytes. Offset by byte n (as well as offset for the correct
//buffer).
#define TX_DATA_BYTE 0x36u

//Receive registers:
#define MCP_RXB0SIDL 0x62u
#define MCP_RXB0DLC 0x65u
#define MCP_RXB0DM 0x66u


//Bit timing:

#define BAUD_RATE_PRESCALE 0x3u
#define BIT_TIME_LENGTH 0x1u
#define PROPAGATION_SEGMENT 0x1u
#define PHASE_SEGMENT_1 0x6u
#define PHASE_SEGMENT_2 0x5u

void can_init(void)
{
		spi_master_init();
		can_ctrl_reset();


		//Modify registers:
		//can_ctrl_bit_modify(TXRTSCTRL, 0b111, 0x0u); //set TXRTSCTRL pins to digital mode (unused)
		//can_ctrl_write(TXRTSCTRL, 0b111u);
													 
		//CNF1, CNF2, CNF3 all left at default values for now. 
		//These control timing, which will be relevant for Node2.
		//

		//CAN bit timing (for node 2):
		can_ctrl_write(MCP_CNF1, BAUD_RATE_PRESCALE);

		uint8_t cnf2_values = (BIT_TIME_LENGTH << 7) | (PHASE_SEGMENT_1) << 3 | (PROPAGATION_SEGMENT);

		can_ctrl_write(MCP_CNF2, cnf2_values);

		can_ctrl_write(MCP_CNF3, PHASE_SEGMENT_2);


		//Disable interrupts
		can_ctrl_write(MCP_CANINTE, 0x0u);
														 
		//Receive any message on RX reg 0.
		can_ctrl_write(MCP_RXB0CTRL, 0xFF); 

		//Receive only Extended ID messages on RX reg 1 
		//(i.e. allow no messages)
		can_ctrl_write(MCP_RXB1CTRL, 0b01000000); 

		//Allow for new message in RX buffer 0.
		can_ctrl_bit_modify(MCP_CANINTF, 0x1u, 0x0); 
													 
		//Disable sending interrupt when message is transmitted	
		can_ctrl_bit_modify(MCP_CANINTE, 0b11100, 0x0u); 

#ifdef LOOPBACK_TEST
		//put CAN controller in loopback mode
		can_ctrl_write(MCP_CANCTRL, MODE_LOOPBACK);
#endif

#ifndef LOOPBACK_TEST
		//put CAN controller in normal mode mode
		//Might need to be replaced with can_ctrl_write();
		can_ctrl_write(MCP_CANCTRL, MODE_NORMAL);
#endif
}


static uint8_t std_id_high_bits(uint16_t id);
static uint8_t std_id_low_bits(uint16_t id);
static uint8_t buffer_status_shift_val(uint8_t buffer_number);

void can_transmit(const can_message_t* p_message, uint8_t tx_buf)
{
		uint8_t shift_val = buffer_status_shift_val(tx_buf); //Used to extract buffer ready state
		uint8_t buffer_offset = 0x10u * tx_buf; //Used to write to the correct buffer

		uint8_t id_high_bits = std_id_high_bits(p_message -> id); //gets the 8 high bits of the message id
		uint8_t id_low_bits = std_id_low_bits(p_message -> id); //gets the 3 low bits + extra info from the message id.
																

		//Waits until the targeted buffer is ready (TXBnXTRL.TXREQ bit is clear).
		while ((can_ctr_read_status() >> shift_val) & 0x1u) 
		{
				//printf("In loop in can_transmit, %4d\n\r",can_ctr_read_status());
				//Do nothing
				//printf("waiting for target buffer to be ready\n\r");
		}


		//Write to transmit buffer:
		
		can_ctrl_write(TX_ID_HIGH + buffer_offset, id_high_bits); //Write identifier high bits
		can_ctrl_write(TX_ID_LOW + buffer_offset, id_low_bits); //Write identifier low bits
		can_ctrl_write(TX_DATA_LEN, (p_message -> data_len)); //Write data length


		for (int byte_n = 0; byte_n < (p_message -> data_len); byte_n ++)
		{
				can_ctrl_write(TX_DATA_BYTE + buffer_offset + byte_n, (p_message -> data)[byte_n]); //Write byte n
		}

		can_ctrl_request_send(0x1u << tx_buf);
}

//returns the shift value to be used to extract buffer "ready"
//status from can_ctr_read_status() function
//defaults to buffer 0 if an illegal buffer number is given.
static uint8_t buffer_status_shift_val(uint8_t buffer_number)
{
		/* 
		 * To check if the given buffer is ready to accept data, we check certain
		 * bits of the value returned by can_ctr_read_status(). The following switch
		 * statement calculates the bitshift required to extract these values.
		 */

		uint8_t shift_val;
		switch (buffer_number)
		{
				case 0:
						shift_val = 2u;
						break;
				case 1:
						shift_val = 4u;
						break;
				case 2:
						shift_val = 6u;
						break;
				default:
						shift_val = 2u;
		}
		return shift_val;
}

//Always reads from buffer 0
uint8_t can_receive(can_message_t* p_message){

		//interrupt on reception not implemented for now.

		if ((can_ctr_read_status() & 0x1u) != 1)
		{
				return 0;
		}
						
		/*		
		while ( (can_ctr_read_status() & 0x1u) != 1) //wait for a message in the receive buffer
		{
				//do nothing
		}
		*/

		uint8_t msg_id_high_bits = can_ctrl_read(MCP_RXB0SIDH);
		uint8_t msg_id_low_bits = can_ctrl_read(MCP_RXB0SIDL);

		(p_message -> id) = (uint16_t) (((uint16_t) (msg_id_high_bits) << 3) + (msg_id_low_bits >> 5));

		(p_message -> data_len) = can_ctrl_read(MCP_RXB0DLC);

		for (int i=0;i<(p_message -> data_len);i++)
		{
				(p_message -> data[i]) = can_ctrl_read(MCP_RXB0DM + i);
		}

		//can_ctrl_bit_modify(MCP_CANINTF, 0x1u, 0x0); //Allow for new message in RX buffer 0.
		can_ctrl_write(MCP_CANINTF, 0x0);
		return p_message -> id;
}

static uint8_t std_id_high_bits(uint16_t id)
{
		return (uint8_t) ((id >> 3) & 0xFF); //gets the 8 high bits of the message id
}

static uint8_t std_id_low_bits(uint16_t id)
{
		uint8_t id_low = (uint8_t) ((id & 0b111) << 5);
		return id_low;
}
