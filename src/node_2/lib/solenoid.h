#ifndef SOLENOID_H
#define SOLENOID_H

#include "sam.h"
#include "time.h"
#include <stdbool.h>
#include <stdio.h>
#include "uart.h"


void solenoid_init(void);
void solenoid_on(void);
void solenoid_off(void);
void solenoid_punch(bool);


#endif