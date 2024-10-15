#include "can_com.h"
#include "can_ctrl.h"
#include "mcp2515.h"


#define TXRTSCTRL 0x0Du
#define FULL_REG_MASK 0xFFu

void can_init(void)
{
		spi_master_init();
		can_ctrl_reset();
		//Modify registers:
				//CNF1, CNF2, CNF3
		can_ctrl_bit_modify(TXRTSCTRL, 0b111, 0x0u); //set TXRTSCTRL pins to digital mode (unused)
				//Filter registers
				//Mask registers
				
		can_ctrl_bit_modify(MCP_CANCTRL, FULL_REG_MASK, MODE_LOOPBACK); //put CAN controller in loopback mode
		//can_ctrl_bit_modify(CANCTRL, FULL_REG_MASK, MODE_NORMAL); //put CAN controller in normal mode mode (to be uncommented after testing on loopback mode)
}
