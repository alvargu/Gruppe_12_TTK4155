#ifndef FONTS_H
#define FONTS_H

#include <avr/pgmspace.h>

#define FONT_LARGE  8
#define FONT_MEDIUM 5
#define FONT_SMALL  4

extern const unsigned char PROGMEM font8[95][FONT_LARGE];
extern const unsigned char PROGMEM font5[95][FONT_MEDIUM];
extern const unsigned char PROGMEM font4[95][FONT_SMALL];

#endif /* FONTS_H_ */