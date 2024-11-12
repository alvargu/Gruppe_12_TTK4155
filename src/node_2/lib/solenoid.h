#ifndef SOLENOID_H
#define SOLENOID_H

#include "sam.h"
#include "time.h"


#define SOLENOID_BOUNCE_DURATION msecs(100);  // 100  [ms]



void solenoid_init(void);
void solenoid_on(void);
void solenoid_off(void);
void solenoid_punch(void);


#endif