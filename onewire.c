/*
 * onewire.c
 *
 *  Created on: 8 Feb 2019
 *      Author: alex
 */
#include "onewire.h"
#include "delay.h"
#include "bitops.h"

#include <msp430.h>

static volatile unsigned char * _dir[] = { &P1DIR, &P2DIR };
static volatile unsigned char * _in[] = { &P1IN, &P2IN };
static volatile unsigned char * _out[] = { &P1OUT, &P2OUT };
static volatile unsigned char * _ren[] = { &P1REN, &P2REN };

OneWire onewire_new(unsigned int port, unsigned int pin) {
    --port;
    OneWire ow;
    ow.dir = _dir[port];
    ow.in = _in[port];
    ow.out = _out[port];
    ow.ren = _ren[port];
    ow.pin = bit(pin);
    set(*ow.out, ow.pin);
    clr(*ow.dir, ow.pin);
    return ow;
}

void onewire_reset(OneWire* pOw) {
    /*
     * During the initialization sequence the bus master transmits (TX)
     * the reset pulse by pulling the 1-Wire bus low for a minimum of 480µs.
     */
    set(*pOw->dir, pOw->pin);   // ONE_WIRE_DIR |=ONE_WIRE_PIN;
    clr(*pOw->out, pOw->pin);   // ONE_WIRE_OUT &= ~ONE_WIRE_PIN;
    DELAY_US(500);              // __delay_cycles(500);

    /*
     * The bus master then releases the bus and goes into receive mode (RX).
     * When the bus is released, the 5kOhm pullup resistor pulls the 1-Wire bus high.
     * When the DS18B20 detects this rising edge, it waits 15µs to 60µs and then transmits
     * a presence pulse by pulling the 1-Wire bus low for 60µs to 240µs.
     */
    set(*pOw->out, pOw->pin);   // ONE_WIRE_OUT |=ONE_WIRE_PIN;
    clr(*pOw->dir, pOw->pin);   // ONE_WIRE_DIR &= ~ONE_WIRE_PIN;
    DELAY_US(500);              // __delay_cycles(500);
}

unsigned int onewire_readByte(OneWire* pOw) {
    char i;
    unsigned int data = 0;

    for(i = 16; i > 0; i--) {

        set(*pOw->dir, pOw->pin);   // ONE_WIRE_DIR |= ONE_WIRE_PIN;
        clr(*pOw->out, pOw->pin);   // ONE_WIRE_OUT &= ~ONE_WIRE_PIN;
        DELAY_US(2);                // __delay_cycles(2);

        set(*pOw->out, pOw->pin);   // ONE_WIRE_OUT |= ONE_WIRE_PIN;
        clr(*pOw->dir, pOw->pin);   // ONE_WIRE_DIR &= ~ONE_WIRE_PIN;
        DELAY_US(8);                // __delay_cycles(8);

        if (read(*pOw->in, pOw->pin)) // if(ONE_WIRE_IN & ONE_WIRE_PIN)
        {
            data |=0x8000;
        }
        data >>= 1;
        DELAY_US(120); // __delay_cycles(120);
    }
    return data;
}

void onewire_writeByte(OneWire* pOw, char data) {
    char i;

    for(i=8;i>0;i--)
    {
        set(*pOw->dir, pOw->pin);   // ONE_WIRE_DIR |=ONE_WIRE_PIN;
        clr(*pOw->out, pOw->pin);   // ONE_WIRE_OUT &= ~ONE_WIRE_PIN;
        DELAY_US(2);                // __delay_cycles(2);
        if(data & 0x01)
        {
            set(*pOw->out, pOw->pin);   // ONE_WIRE_OUT |= ONE_WIRE_PIN;
        }
        DELAY_US(60);               // __delay_cycles(60);
        set(*pOw->out, pOw->pin);   // ONE_WIRE_OUT |= ONE_WIRE_PIN;
        clr(*pOw->dir, pOw->pin);   // ONE_WIRE_DIR &= ~ONE_WIRE_PIN;
        data >>=1;
    }
}
