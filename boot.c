/*
 * boot.c
 *
 *  Created on: 5 Feb 2019
 *      Author: alex
 */
#include "boot.h"
#include "display.h"
#include <msp430.h>
#include <inttypes.h>

void boot() {
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode to activate previously configured port settings
    __enable_interrupt();       // enable interrupts

    displayInit();
}

