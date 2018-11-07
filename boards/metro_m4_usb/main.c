#include <atmel_start.h>
#include "atmel_start_pins.h"
#include "pins.h"               // local

extern void npx_main(void);

void delay_some(void) {
    for (volatile int i = 230001; i > 0; i--) {
    }
}

void blink(void) {
    reset_d13();
    delay_some();
    toggle_d13();
    delay_some();
    toggle_d13();
}

void blinks(void) {
    for (int k = 3; k > 0; k--) {
        for (int j = 3; j > 0; j--) {
            delay_some();
        }                       // offer a pattern
        for (int i = 3; i > 0; i--) {
            blink();
        }
    }
}

// int main(void)
void main_cf(void) {
    /* Initializes MCU, drivers and middleware */
    atmel_start_init();
    pins_setup();
    npx_main();

    /* Replace with your application code */
    // blinks();
    // main_app();
    cdcd_acm_example();
    while (1) {
    }
}

int main(void) {
    main_cf();
}
