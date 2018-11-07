#ifndef LIB_BSP_NEOPIX_H
#define LIB_BSP_NEOPIX_H

// #include "PinMap.h"

// trellis M4 PA27
// metro   M4 PB22
// metro   M4 PA17 - D12 - alternate for NeoPixel external array

#define PORTA 0
#define PORTB 1

// #define HAS_PORTB

extern void neopix_show_400k(uint32_t pin, uint8_t *pixels, uint16_t numBytes);
extern void neopix_show_800k(uint32_t pin, uint8_t *pixels, uint16_t numBytes);

#endif
