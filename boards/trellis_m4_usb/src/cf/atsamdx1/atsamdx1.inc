/****h* camelforth/atsamdx1/atsamdx1.inc
 *
 * from:
 ****h* camelforth/tivaio.c
 *
 * NAME
 *  atsamdx1.inc
 * DESCRIPTION
 *  Terminal I/O, and main entry point for
 *  CamelForth in C, for the ATSAMD51J19A and ATSAMD21G18A
 *  Adafruit Metro M4 Express target board,
 *  Adafruit Feather M0 Express target board.
 * SYNOPSIS
 *  Provides the functions
 *      void putch(char c)      write one character to terminal
 *      char getch(void)        await/read one character from keyboard
 *      int getquery(void)      return true if keyboard char available
 *      void initTermios(void)  NOT IMPLEMENTED - configure terminal for Forth
 *      void resetTermios(void) NOT IMPLEMENTED - reset terminal configuration, if req'd
 *      void camelforth(void)   main entry point for SAMDx1.   UPSTREAM: int main(void)
 *
 * AUTHORS
 *  Brad Rodriguez
 *  wa1tnr September, 2018
 ******
 * LICENSE TERMS
 *  CamelForth in C
 *  copyright (c) 2016,2017 Bradford J. Rodriguez.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Commercial inquiries should be directed to the author at
 *  115 First St., #105, Collingwood, Ontario L9Y 4W3 Canada
 *  or via email to bj@camelforth.com
 */

#include <atmel_start.h>
#include "atsamdx1.h"
#include "atsamdx1_getkey_usb.inc"
#include "cut.inc"              // string cutter utility, for long USB printf's

extern unsigned int getKey(void);       // hardware-independent wrapper

/*
#include <stdint.h>
#include <stdbool.h>
*/

// #define NULL 0  // already defined for Atmel Start and gcc:

/*
 * Terminal I/O functions
 */

/* USB based */
#define printf(format,integer) \
    print_string[0] = (uint32_t) "\0"; \
    sprintf(print_string, format, integer); \
        chopped_acm_write(print_string)

#define getch getKey

void putch(char c) {
    char *p;
    p = &c;
    c = *p + 0;
    print_string[0] = c;
    print_string[1] = '\0';
    chopped_acm_write(print_string);
}

int getquery(void) {
    return -1;                  /* TODO wa1tnr */
}

/****f* main/main
 * NAME
 *  main
 * SYNOPSIS
 *  int main(void)
 * DESCRIPTION
 *  Main program, entered after an MCU reset.
 ******
 */

void ESC_lb(void) {
    char ch[0];
    ch[0]='\033'; // ESCape
    putch(ch[0]);
    ch[0]='\133'; // [
    putch(ch[0]);
}

void bg_blue(void) {
    ESC_lb();
    strcpy(print_string, "44m");
    chopped_acm_write(print_string);
}

void fg_yellow(void) {
    ESC_lb();
    strcpy(print_string, "0;1;33m");
    chopped_acm_write(print_string);
}

void color_reset(void) {
    ESC_lb();
    strcpy(print_string, "0m");
    chopped_acm_write(print_string);
}

void pad_one_space(void) {
    putch('\040');
}

void interpreter(void);         /* forward reference */

void camelforth(void) {
    for (volatile int i = 7080706; i > 0; i--) {
    }

    strcpy(print_string, "\n\n");
    chopped_acm_write(print_string);

    fg_yellow();
    bg_blue();

    pad_one_space();

/*
    strcpy(print_string, "On branch master");
    strcpy(print_string, "On branch ainsu-CamelForth-d51-usb");
*/
    strcpy(print_string, "On branch master");
    chopped_acm_write(print_string);

    pad_one_space();

    color_reset();

    strcpy(print_string, "\n\nTue Nov  6 01:58:07 UTC 2018");
    chopped_acm_write(print_string);

    strcpy(print_string, "\n\ncamelforth()\n\n");
    chopped_acm_write(print_string);

    fg_yellow();

    while (1) {                 /* loop in case interpreter() ever terminates */
        interpreter();
    }
}
