/*
 * led.c
 *
 *  Created on: 8 Feb 2019
 *      Author: alex
 */
#include "led.h"
#include "types.h"
#include "bitops.h"

#include <msp430.h>

#define _LED_NEW(port, pin) set(P##port##DIR, bit(pin)); clr(P##port##OUT, bit(pin))

void led_new(eLed led) {
    switch(led) {
    case LED_RED:
        _LED_NEW(1,0);
        break;
    case LED_GREEN:
        _LED_NEW(9,7);
        break;
    default:
        break;
    }
}

void led_on(eLed led) {
    switch(led) {
    case LED_RED:
        set(P1OUT, bit(0));
        break;
    case LED_GREEN:
        set(P9OUT, bit(7));
        break;
    default:
        break;
    }
}

void led_off(eLed led) {
    switch(led) {
    case LED_RED:
        clr(P1OUT, bit(0));
        break;
    case LED_GREEN:
        clr(P9OUT, bit(7));
        break;
    default:
        break;
    }
}

void led_toggle(eLed led) {
    switch(led) {
    case LED_RED:
        tog(P1OUT, bit(0));
        break;
    case LED_GREEN:
        tog(P9OUT, bit(7));
        break;
    default:
        break;
    }
}

