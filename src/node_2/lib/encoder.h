#ifndef ENCODER_H
#define ENCODER_H

// Include libraries needed.
#include "sam.h"
#include <stdint.h>
#include "time.h"

// PC26 = ChA (D4)
// PC25 = ChB (D5)
#define _ENCODER_A_PIN PIO_PC25
#define _ENCODER_B_PIN PIO_PC26
// Define max step size for the motor box enclosure (Measured experimentally +-20)
#define _ENCODER_STEP_MAX 1385 

void encoder_init(void);
uint8_t encoder_get_pos(void);
void encoder_pos_rst(void);

#endif