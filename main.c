#include "boot.h"
#include "test.h"
#include "led.h"
#include "button.h"
#include "thermometer.h"
#include "display.h"
#include "pump.h"

#include <stdint.h>

// typedefs
typedef enum { COLLECTOR, WATER, THERMOMETER_SIZE } eTemperature;
typedef enum { ENABLED, OVERHEAT, NODIFF } eCircuitState;
typedef enum { OK, HEATING } eControlState;
typedef enum { CONTROL, SETTING } eSystemState;

// defines
#define COLLECTOR_ID    0x0D0114339EA1D228
#define WATER_ID        0x8A01143392748328
#define IDLE_TIMEOUT    10000LL
#define TARGET_DEFAULT  26.0
#define DISPLAY_DEFAULT WATER
#define MAX_DOWN        45.0
#define MAX_UP          38.0
#define DIFF_UP         3.0
#define DIFF_DOWN       1.0

// static variables
static deviceaddress_t thermometers[THERMOMETER_SIZE] = { COLLECTOR_ID, WATER_ID };
static uint64_t idleCountdown = IDLE_TIMEOUT;
static float target = TARGET_DEFAULT;
static eTemperature temperatureDisplay = DISPLAY_DEFAULT;

static float temperatures[THERMOMETER_SIZE] = { 0.0 };
static eCircuitState circuit = ENABLED;
static eControlState water = OK;
static eSystemState systemState = CONTROL;


void measure() {
    thermometer_getTemperaturesC(temperatures, thermometers, THERMOMETER_SIZE);
}

void act() {
    if (temperatures[COLLECTOR] > MAX_DOWN)
        circuit = OVERHEAT;

    if ((temperatures[COLLECTOR] - temperatures[WATER]) < DIFF_DOWN)
        circuit = NODIFF;

    if (circuit == OVERHEAT && temperatures[COLLECTOR] < MAX_UP)
        circuit = ENABLED;

    if (circuit == NODIFF && (temperatures[COLLECTOR] - temperatures[WATER]) > DIFF_UP)
        circuit = ENABLED;

    if (water == OK && temperatures[WATER] < target)
        water = HEATING;

    if (water == HEATING && temperatures[WATER] >= target)
        water = OK;

    if (circuit == ENABLED && water == HEATING)
        setPumpState(PUMP_ON);
    else
        setPumpState(PUMP_OFF);
}

void display() {
    if (systemState == SETTING)
    {
        displayTemperature(target);
        led_on(LED_RED);
    }
    else {
        displayTemperature(temperatures[temperatureDisplay]);
        displayHRT(water);
        displayEXC(circuit == OVERHEAT);
        displayANT(circuit == NODIFF);
        displayTMR(circuit == ENABLED);
        led_off(LED_RED);
    }
}

void control() {
    measure();
    act();
    display();
}

void idleTimeout()
{
    if (systemState == SETTING)
        systemState = CONTROL;

    if (systemState == CONTROL)
        control();
}

void onButtonRight()
{
    if (systemState == CONTROL)
        temperatureDisplay ^= 1;
    else {
        idleCountdown = IDLE_TIMEOUT * 20;
        target += 0.5;
    }

    display();
}

void onButtonLeft()
{
    if (systemState == CONTROL) {
        systemState = SETTING;
    }
    else {
        target -= 0.5;
    }

    idleCountdown = IDLE_TIMEOUT * 20;

    display();
}

void setup()
{
    boot();
    led_new(LED_RED);
    led_new(LED_GREEN);
    button_new(BUTTON_LEFT, onButtonLeft);
    button_new(BUTTON_RIGHT, onButtonRight);
    control();
}

void loop()
{
    if (!idleCountdown--)
    {
        idleTimeout();
        idleCountdown = IDLE_TIMEOUT;
    }
}

void test()
{
    ledTest();
    buttonTest();
    displayTest();
    deviceIdTest();
    temperatureManyTest();
}

int main(void)
{
    setup();
    //test();
    while (1)
    {
        loop();
    }
}

/*
 * DONE:
 * add button driver
 * add display driver
 * add LED driver
 * do some wiring like in the wiring image
 * read ROM command is for one device only
 * add OneWire and Temperature Reader
 * correct temperature interpretation
 * include ids of other temperature sensors (maybe label them too)
 * add Control logic
 * test control logic by using leds (at first)
 */
