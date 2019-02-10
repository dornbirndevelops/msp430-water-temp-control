/*
 * onewire.h
 *
 *  Created on: 8 Feb 2019
 *      Author: alex
 */

#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#include <stdint.h>

typedef struct {
    volatile unsigned char* dir;
    volatile unsigned char* out;
    volatile unsigned char* in;
    volatile unsigned char* ren;
    uint8_t pin;
    unsigned parasitic;
} OneWire;

/*
 * creates a new onewire connection bus at given port and pin.
 */
OneWire onewire_new(unsigned int port, unsigned int pin);

/*
 * Perform a 1-Wire reset cycle.
 */
void onewire_reset(OneWire*);

// unsigned onewire_readBit(OneWire*);
// void onewire_writeBit(OneWire*, unsigned);

unsigned int onewire_readByte(OneWire*);
void onewire_writeByte(OneWire*, char);

#endif /* ONEWIRE_H_ */
