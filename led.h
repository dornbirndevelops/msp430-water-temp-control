/*
 * led.h
 *
 *  Created on: 8 Feb 2019
 *      Author: alex
 */

#ifndef LED_H_
#define LED_H_

typedef enum
{
    LED_RED, LED_GREEN
} eLed;

void led_new(eLed);
void led_on(eLed);
void led_off(eLed);
void led_toggle(eLed);

#endif /* LED_H_ */
