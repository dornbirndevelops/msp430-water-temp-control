/*
 * thermometer.c
 *
 *  Created on: 13 Feb 2019
 *      Author: alex
 */
#include "thermometer.h"

#include "onewire.h"

#include <msp430.h>

// DS18B20 rom commands
#define SEARCHROM       0xF0
#define READROM         0x33
#define MATCHROM        0x55
#define SKIPROM         0xCC
#define ALARMSEARCH     0xEC

// DS18B20 function commands
#define CONVERTT        0x44
#define WRITESCRATCHPAD 0x4E
#define READSCRATCHPAD  0xBE
#define COPYSCRATCHPAD  0x48
#define RECALLE2        0xB8
#define READPOWERSUPPLY 0xB4

deviceaddress_t thermometer_getAddress()
{
    onewire_reset();
    onewire_write8(READROM);
    return onewire_read64();
}

float _convertRawTemperatureC(uint16_t rawTemp)
{
    if (rawTemp >= 0x8000)
    {
        rawTemp = (~rawTemp) + 1;
    }
    return ((float) rawTemp * 0.0625);
}

float _readTemperatureC(deviceaddress_t device)
{
    onewire_reset();
    onewire_write8(MATCHROM);
    onewire_write64(device);
    onewire_write8(READSCRATCHPAD);
    uint16_t rawTemp = onewire_read16();
    return _convertRawTemperatureC(rawTemp);
}

void thermometer_getTemperaturesC(float * const temperatures,
                                  deviceaddress_t const * const devices,
                                  uint16_t count)
{
    onewire_reset();
    onewire_write8(SKIPROM);
    onewire_write8(CONVERTT);

    __delay_cycles(800000);
    while (count--)
    {
        temperatures[count] = _readTemperatureC(devices[count]);
    }
}
