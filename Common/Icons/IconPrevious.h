#ifndef ICONPREVIOUS_H
#define ICONPREVIOUS_H

#include <avr/pgmspace.h>

#define icon_previous_width 10
#define icon_previous_height 10

const unsigned char icon_previous_bits[] PROGMEM = {
   0xe0, 0x01, 0xf0, 0x00, 0x78, 0x00, 0x3c, 0x00, 0x1e, 0x00, 0x1e, 0x00,
   0x3c, 0x00, 0x78, 0x00, 0xf0, 0x00, 0xe0, 0x01 };

#endif