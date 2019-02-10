/*
 * temperature.c
 *
 *  Created on: 9 Feb 2019
 *      Author: alex
 */
#include "temperature.h"
#include "delay.h"
#include "temp.h"

Thermometer thermometer_new(OneWire *pOw, const uint8_t address)
{
    Thermometer t = { .pOw = pOw, .address = address };
    return t;
}

float thermometer_readTemperatureCelsius(Thermometer* pThermometer)
{
    unsigned int temperature; // unsigned int temp;

    onewire_reset(pThermometer->pOw); // reset_18B20();
    onewire_writeByte(pThermometer->pOw, DS18B20_SKIP_ROM); // skip ROM command, send_18B20(0xcc);
    onewire_writeByte(pThermometer->pOw, DS18B20_CONVERT_T); // convert T command, send_18B20(0x44);
    DELAY_US(800); // __delay_cycles(800);

    onewire_reset(pThermometer->pOw); // reset_18B20();
    onewire_writeByte(pThermometer->pOw, DS18B20_SKIP_ROM); // skip ROM command, send_18B20(0xcc);
    onewire_writeByte(pThermometer->pOw, DS18B20_READ_SCRATCHPAD); // convert T command, send_18B20(0xbe);

    temperature = onewire_readByte(pThermometer->pOw); // temp = read_18B20();

    if (temperature >= 0x8000)
    {
        temperature = (~temperature) + 1;
    }

    volatile float a = ((float) temperature / 8.0); // return((float)temp/8.0);
    volatile float b = get_temp();
    return a;
}
