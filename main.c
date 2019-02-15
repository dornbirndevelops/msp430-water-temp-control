#include "boot.h"
#include "test.h"

#include <stdint.h>

#define STARTUP_MODE 0
volatile unsigned char mode = STARTUP_MODE;

int main(void)
{
    boot();
    //ledTest();
    //buttonTest();
    //displayTest();
    while (1)
    {
        //deviceIdTest();
        temperatureManyTest();
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
 *
 * TODO:
 *
 * add Control logic
 * test control logic by using leds (at first)
 * add pumping circuit
 * enjoy
 */
