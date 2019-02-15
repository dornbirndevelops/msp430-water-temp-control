/*
 * test.c
 *
 *  Created on: 9 Feb 2019
 *      Author: alex
 */
#include "test.h"

#include "delay.h"
#include "led.h"
#include "button.h"
#include "display.h"
#include "thermometer.h"
#include <msp430.h>

void delayTest()
{
    static unsigned value = 0;
    DELAY_MS(1000);
    value ^= 1;
    displayHRT(value);
}

void ledTest()
{
    led_new(LED_RED);
    led_new(LED_GREEN);

    led_on(LED_RED);
    led_toggle(LED_GREEN);

    led_off(LED_RED);
    led_toggle(LED_GREEN);
}

void noopLeft()
{
    // should be visited when left button is pressed
}

void noopRight()
{
    // should be visited when right button is pressed
}

void buttonTest()
{
    button_new(BUTTON_LEFT, &noopLeft);
    button_new(BUTTON_RIGHT, &noopRight);
}

void displayTest()
{
    displayTemperature(0.0);
    displayTemperature(-1.0);
    displayTemperature(-1.5);
    displayTemperature(-1.65);
    displayTemperature(1.0);
    displayTemperature(1.5);
    displayTemperature(1.65);
    displayTemperature(-1234.56);

    displayBattery(6);
    displayHRT(1);
    displayTMR(1);
    displayEXC(1);
    displayREC(1);
    displayANT(1);
    displayTX(1);
    displayRX(1);
    displayText("TADAAH");
    displayScrollText("HALLO WELT DIESER TEXT KOMMT VON ALEX");
}

void deviceIdTest()
{
    volatile deviceaddress_t device = 0;
    device = thermometer_getAddress();
    __delay_cycles(200000);
}

#define THERMOMETER_COUNT 3
static float temperatures[THERMOMETER_COUNT] = { 0.0 };
static deviceaddress_t devices[THERMOMETER_COUNT] = {
    0x0D0114339EA1D228,
    0x8A01143392748328,
    0x8402131D69F9AA28
};

void temperatureManyTest()
{
    thermometer_getTemperaturesC(temperatures, devices, THERMOMETER_COUNT);
    uint8_t i = THERMOMETER_COUNT;
    while (i--)
    {
        displayTemperature(temperatures[i]);
        __delay_cycles(5000000);
    }
}
