#pragma once

#include <stdint.h>



// Time is a count of the number of ticks, and is represented as a uint64_t
// Time is used to mean both absolute time since device start, and a duration

// Return the time since the device was started.
uint64_t time_now(void);

// Convert standard wall time units to ticks
uint64_t usecs(uint64_t s);
uint64_t msecs(uint64_t s);
uint64_t seconds(uint64_t s);
uint64_t minutes(uint64_t s);
uint64_t hours(uint64_t s);

// Convert ticks to wall time units
float totalUsecs(uint64_t t);
float totalMsecs(uint64_t t);
float totalSeconds(uint64_t t);
float totalMinutes(uint64_t t);
float totalHours(uint64_t t);

// Spins the CPU (delays) for a duration
// Example:
//   time_spinFor(mescs(200));
void time_spinFor(uint64_t duration);

// Spins the CPU (delays) until some time after device start
void time_spinUntil(uint64_t then);

// Performs a body periodically
// Example:
//   time_doPeriodic(msecs(50)){
//       // do stuff
//   }    
#define time_doPeriodic(period) \
    for(uint64_t then = time_now() + (period); 1; then += (period), time_spinUntil(then))

// Human-readable time
typedef struct Time Time;
struct Time {
    uint16_t ticks;
    uint16_t msecs;
    uint8_t  seconds;
    uint8_t  minutes;
    uint16_t hours;
};

// Split ticks into human-readable form
Time time_split(uint64_t t);

// Convert human-readable time into ticks
uint64_t time_combine(Time t);

// Convenience macros for printing human-readable `Time`s.
// Example:
//      Time t = (Time){.hours = 1, .minutes = 5, .seconds = 48, .msecs = 2};
//      printf("t: " time_fmtStr "\n", time_fmtParam(t));
//      // prints "t: Time(1h, 5m, 48s, 2ms, 0t)"
#define time_fmtStr "Time(%uh, %um, %us, %ums, %ut)"
#define time_fmtParam(t) t.hours, t.minutes, t.seconds, t.msecs, t.ticks