#ifndef LIB_BSP_NEOPIX_H
#define LIB_BSP_NEOPIX_H

// EXTERN_NPX defined in driver_init.h
#include "driver_init.h"

// trellis M4 PA27
// metro   M4 PB22
// metro   M4 PA17 - D12 - alternate for NeoPixel external array

#define PORTA 0
#define PORTB 1

#undef HAS_PORTB

#ifdef EXTERN_NPX
    #undef HAS_PORTB
    // PA17 D12 Metro M4 Express
    #define NEOPIX_PIN 17
#endif

#ifndef EXTERN_NPX
    #define HAS_PORTB
    // PB22 - internal NeoPixel - Metro M4 Express
    // 22 + 32 = 54
    #define NEOPIX_PIN 54
#endif

extern void neopix_show_400k(uint32_t pin, uint8_t *pixels, uint16_t numBytes);
extern void neopix_show_800k(uint32_t pin, uint8_t *pixels, uint16_t numBytes);

#endif
