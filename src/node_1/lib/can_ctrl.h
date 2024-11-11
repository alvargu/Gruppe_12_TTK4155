#ifndef CAN_CTRL_H
#define CAN_CTRL_H

#include <stdint.h>

//Resets CAN controller and sets required registers to initialize
//CAN controller
void can_ctrl_reset(void);

//Initiate message transmission for one or more transmit buffers.
//Bit 0 (LSB) of transmit_buffer = 1 enables buffer 0, = 0 disables buffer 0
//Bit 1 controls buffer 1
//Bit 2 controls buffer 2
//Higher order bits are ignored
void can_ctrl_request_send(uint8_t transmit_buffer);

//Reads one byte of data from the adressed register in the CAN controller
uint8_t can_ctrl_read(uint8_t reg_adress);

//Writes one byte of data to the adressed register in the CAN controller
void can_ctrl_write(uint8_t reg_adress, uint8_t data);

//Modifies the adressed register with the given mask and data.
void can_ctrl_bit_modify(uint8_t reg_adress, uint8_t mask, uint8_t data);

//Returns 8 status bits from the CAN controller as follows:
//Bit 0 (LSB) : CANINTF.RX0IF
//Bit 1		  : CANINTFL.RX1IF
//Bit 2		  : TXB0CNTRL.TXREQ
//Bit 3		  : CANINTF.TX0IF
//Bit 4		  : TXB1CNTRL.TXREQ
//Bit 5		  : CANINTF.TX1IF
//Bit 6		  : TXB2CNTRL.TXREQ
//Bit 7 (MSB) : CANINTF.TX2IF
uint8_t can_ctr_read_status(void);
#endif
