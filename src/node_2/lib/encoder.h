#ifndef ENCODER_H
#define ENCODER_H

// Include libraries needed.
#include <sam.h>
#include <stdio.h>
#include <stdlib.h>
#include "time.h"


void encoder_init(void);
uint16_t encoder_pos(void);

#endif