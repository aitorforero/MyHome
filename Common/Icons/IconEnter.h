#ifndef ICONENTER_H
#define ICONENTER_H

#include <avr/pgmspace.h>

#define icon_enter_width 10
#define icon_enter_height 10

const unsigned char icon_enter_bits[] PROGMEM = {
   0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x04, 0x02, 0x02, 0x02, 0xff, 0x03,
   0x02, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 };
   
#endif