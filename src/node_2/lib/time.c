#include <sam.h>
#include <stdio.h>
#include <stdlib.h>
#include "time.h"


uint64_t calib;
static uint64_t now = 0;
    
__attribute__((constructor)) void time_init(void){
    // Clock calibration is set to '(num cycles for 1ms) / 8'
    // (SysTick is by default set to use 8x clock divisor)
    calib = SysTick->CALIB * 8;
    // Set reload at calib-1 ticks 
	SysTick->LOAD = (calib & SysTick_LOAD_RELOAD_Msk)-1;
    // Reset counter
	SysTick->VAL = 0; 
    // Set interrupt priority
	NVIC_SetPriority(SysTick_IRQn, 2);
	SysTick->CTRL = 
        ((1 << SysTick_CTRL_CLKSOURCE_Pos) & SysTick_CTRL_CLKSOURCE_Msk)    |   // No 8x divisor
	    ((1 << SysTick_CTRL_TICKINT_Pos)   & SysTick_CTRL_TICKINT_Msk)      |   // Enable interrupt
	    ((1 << SysTick_CTRL_ENABLE_Pos)    & SysTick_CTRL_ENABLE_Msk);	        // Enable SysTick
}    


void SysTick_Handler(void){
    now += calib;
}


uint64_t time_now(void){
    return now + calib - SysTick->VAL;
}


uint64_t usecs(uint64_t s){
    return s*calib/1000;
}
uint64_t msecs(uint64_t s){
    return s*calib;
}
uint64_t seconds(uint64_t s){
    return s*1000*calib;
}
uint64_t minutes(uint64_t s){
    return s*60*1000*calib;
}
uint64_t hours(uint64_t s){
    return s*60*60*1000*calib;
}

float totalUsecs(uint64_t t){
    return t / (1.0 * calib / 1000);
}    
float totalMsecs(uint64_t t){
    return t / (1.0 * calib);
}
float totalSeconds(uint64_t t){
    return t / (1.0 * calib * 1000);
}
float totalMinutes(uint64_t t){
    return t / (1.0 * calib * 1000 * 60);
}
float totalHours(uint64_t t){
    return t / (1.0 * calib * 1000 * 60 * 60);
}

Time time_split(uint64_t t){
    Time r;
    uint64_t d;
    d = t / (calib*1000*60*60);
    r.hours = d;
    t = t - d * (calib*1000*60*60);
    
    d = t / (calib*1000*60);
    r.minutes = d;
    t = t - d * (calib*1000*60);
    
    d = t / (calib*1000);
    r.seconds = d;
    t = t - d * (calib*1000);
    
    d = t / (calib);
    r.msecs = d;
    r.ticks = t - d * calib;
    return r;
}

uint64_t time_combine(Time t){
    uint64_t a = 0;
    a += t.ticks + msecs(t.msecs) + seconds(t.seconds) + minutes(t.minutes) + hours(t.hours);
    return a;
}     

void time_spinFor(uint64_t duration){
    time_spinUntil(time_now() + duration);
}    

void time_spinUntil(uint64_t then){
    while(then > time_now()){}        
}    

uint64_t ticksPerMs(void){
    return calib;
}

