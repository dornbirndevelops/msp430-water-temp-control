#include "boot.h"
#include "test.h"

#define STARTUP_MODE 0
volatile unsigned char mode = STARTUP_MODE;

int main(void)
{
    boot();
    //ledTest();
    //buttonTest();
    //displayTest();
    temperatureTestAlex();

    while (1) {
        //delayTest();
        temperatureTest();

    }
}

/*
 * DONE:
 * add button driver
 * add display driver
 * add LED driver
 * do some wiring like in the wiring image
 *
 * TODO:
 *
 * read ROM command is for one device only
 *
 * add OneWire and Temperature Reader
 *
 *
 *
 * add Control logic
 * test control logic by using leds (at first)
 * add pumping circuit
 * enjoy
 */
