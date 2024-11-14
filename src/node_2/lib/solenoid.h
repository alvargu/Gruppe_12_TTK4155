#ifndef SOLENOID_H
#define SOLENOID_H

#include "sam.h"
#include "time.h"
#include <stdbool.h>
#include <stdio.h>

#define SOLENOID_BOUNCE_DURATION msecs(50)  // 100  [ms]
#define SOLENOID_LOCK_DURATION msecs(250)

void solenoid_init(void);
void solenoid_on(void);
void solenoid_off(void);
void solenoid_punch(void);


#endif