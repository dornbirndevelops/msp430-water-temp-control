/*
 * pump.c
 *
 *  Created on: 17 Feb 2019
 *      Author: alex
 */
#include "pump.h"
#include "led.h"

void setPumpState(ePumpState state) {
    if(state) {
        led_on(LED_GREEN);
    }
    else {
        led_off(LED_GREEN);
    }
}
