/*
 * onewire.c
 *
 *  Created on: 8 Feb 2019
 *      Author: alex
 */
#include "onewire.h"

#include <msp430.h>

// configurables
#define OWDIR   P2DIR
#define OWIN    P2IN
#define OWOUT   P2OUT
#define OWBIT   BIT1

// implementation
#define OWTX OWDIR |= OWBIT
#define OWRX OWDIR &= ~OWBIT
#define OWHI OWOUT |= OWBIT
#define OWLO OWOUT &= ~OWBIT
#define OWRD OWIN & OWBIT

void onewire_reset()
{
    OWTX;
    OWLO;
    __delay_cycles(500);
    OWHI;
    OWRX;
    __delay_cycles(500);
}

void onewire_write8(uint8_t data)
{
    uint8_t i = 8;

    while (i--)
    {
        OWTX;
        OWLO;
        __delay_cycles(2);
        if (data & (1 << 0))
        {
            OWHI;
        }
        __delay_cycles(60);
        OWHI;
        OWRX;
        data >>= 1;
    }
}

void onewire_write16(uint16_t data)
{
    uint8_t i = 16;

    while (i--)
    {
        OWTX;
        OWLO;
        __delay_cycles(2);
        if (data & (1 << 0))
        {
            OWHI;
        }
        __delay_cycles(60);
        OWHI;
        OWRX;
        data >>= 1;
    }
}

void onewire_write32(uint32_t data)
{
    uint8_t i = 32;

    while (i--)
    {
        OWTX;
        OWLO;
        __delay_cycles(2);
        if (data & (1 << 0))
        {
            OWHI;
        }
        __delay_cycles(60);
        OWHI;
        OWRX;
        data >>= 1;
    }
}

void onewire_write64(uint64_t data)
{
    uint8_t i = 64;

    while (i--)
    {
        OWTX;
        OWLO;
        __delay_cycles(2);
        if (data & (1 << 0))
        {
            OWHI;
        }
        __delay_cycles(60);
        OWHI;
        OWRX;
        data >>= 1;
    }
}

uint8_t onewire_read8()
{
    uint8_t data = 0;
    uint8_t mask = 1;
    while (mask)
    {
        OWTX;
        OWLO;
        __delay_cycles(2);
        OWHI;
        OWRX;
        __delay_cycles(8);
        if (OWRD)
        {
            data |= mask;
        }
        mask <<= 1;
        __delay_cycles(60);
    }
    return data;
}

uint16_t onewire_read16()
{
    uint16_t data = 0;
    uint16_t mask = 1;
    while (mask)
    {
        OWTX;
        OWLO;
        __delay_cycles(2);
        OWHI;
        OWRX;
        __delay_cycles(8);
        if (OWRD)
        {
            data |= mask;
        }
        mask <<= 1;
        __delay_cycles(60);
    }
    return data;
}

uint32_t onewire_read32()
{
    uint32_t data = 0;
    uint32_t mask = 1;
    while (mask)
    {
        OWTX;
        OWLO;
        __delay_cycles(2);
        OWHI;
        OWRX;
        __delay_cycles(8);
        if (OWRD)
        {
            data |= mask;
        }
        mask <<= 1;
        __delay_cycles(60);
    }
    return data;
}

uint64_t onewire_read64()
{
    uint64_t data = 0;
    uint64_t mask = 1;
    while (mask)
    {
        OWTX;
        OWLO;
        __delay_cycles(2);
        OWHI;
        OWRX;
        __delay_cycles(8);
        if (OWRD)
        {
            data |= mask;
        }
        mask <<= 1;
        __delay_cycles(60);
    }
    return data;
}
