// leverages adafruit seesaw code bsp_neopixel.cpp

// see the src/cf/bsp directory

#include "sam.h"
#include "bsp_neopix.h"

// trellis M4 PA27

#define NEOPIX_PIN 27

void uSec(void) {
    for (volatile int i = 1; i < 2; i++) { // needs calibration
        // nothing
    }
}

void short_timer(void) { // human blinkie timescale
    uint32_t on_time  = 2140111222; // it's 2147 something ;)
    for(on_time = 214011; on_time > 0; on_time--) {
        uSec();
    }
}

void wide_timer(void) { // human blinkie timescale
    uint32_t on_time  = 2140111222; // it's 2147 something ;)
    // for(on_time = 214011; on_time > 0; on_time--) {

    // two hundred thousand was a bit slow
    for(on_time = 132022; on_time > 0; on_time--) {
        uSec();
    }
}

uint32_t color = 0;

void to_color(void) {
    neopix_show_800k(NEOPIX_PIN, (uint8_t *)&color, 4);
    wide_timer();
}

void to_color_st(void) {
    neopix_show_800k(NEOPIX_PIN, (uint8_t *)&color, 4);
    short_timer();
}

void flicker_npx(void) {
    color = 0x090000;    // blue   //
    to_color_st();
    color = 0x000000;    // dark //
    to_color_st();
}

void blinkfast(void) {
    for(int i = 5; i > 0; i--) {
        flicker_npx();
    }
}

void color_magenta(void) {
    color = 0x090900;    // magenta //
}

void color_blue(void) {
    color = 0x090000;    // blue   //
}

void color_blink(void) {
    to_color();
    short_timer();
}

void quick_npx_demo(void) {
    for(int i = 5; i > 0; i--) {
        color_magenta();
        color_blink();
	color_blue();
        color_blink();
    }
}

void neo_pixel_demo(void) {

    quick_npx_demo();
    quick_npx_demo();

    blinkfast();
    to_color();

    //        BBRRGG
    color = 0x090000;    // blue   //
    to_color();

    color = 0x000000;    // dark //
    to_color();

    wide_timer(); wide_timer(); wide_timer();

    color = 0x001903;    // orange //
    to_color();

    color = 0x090900;    // magenta //
    to_color();
    color = 0x000009;    // green  //
    to_color();

    // color = 0x090000;    // blue   //
    color = 0x010000;    // blue   //
    to_color();

/*
    color = 0x000900;    // red    //
    to_color();
    color = 0x001903;    // orange //
    to_color();
*/
}

void npx_main(void) {
    neo_pixel_demo();
}
