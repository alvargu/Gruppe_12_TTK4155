#ifndef ENCODER_H
#define ENCODER_H

// Include libraries needed.
#include "sam.h"
#include <stdint.h>
#include "time.h"


void encoder_init(void);
uint8_t encoder_get_pos(void);
void encoder_pos_rst(void);

#endif