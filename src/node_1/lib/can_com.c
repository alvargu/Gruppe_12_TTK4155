#include "can_com.h"
#include "can_ctrl.h"

#define XRTSCTRL ((uint8_t) 0x0D)
#define CANCTRL ((uint8_t) 0x0F)
#define CNF1 ((uint8_t) 0x2A)
#define CNF2 ((uint8_t) 0x29)
#define CNF3 ((uint8_t) 0x28)


void can_init(void)
{
		can_ctrl_reset();
		//Modify registers:
				//CNF1, CNF2, CNF3
		can_ctrl_bit_modify(XRTSCTRL, 0b111, 0x0u); //set XRTSCTRL pins to digital mode (unused)
				//Filter registers
				//Mask registers
				
		can_ctrl_bit_modify(CANCTRL, 0xFFu, 0b01000000); //put CAN controller in loopback mode
		//can_ctrl_bit_modify(CANCTRL, 0xFFu, 0x0u); //put CAN controller in normal mode mode (future)
}
