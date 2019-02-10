/*
 * temperature.h
 *
 *  Created on: 8 Feb 2019
 *      Author: alex
 */

#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#include "onewire.h"

// DS18B20 rom commands
#define DS18B20_SEARCH_ROM 0xF0
#define DS18B20_READ_ROM 0x33
#define DS18B20_MATCH_ROM 0x55
#define DS18B20_SKIP_ROM 0xCC
#define DS18B20_ALARM_SEARCH 0xEC

// DS18B20 function commands
#define DS18B20_CONVERT_T 0x44
#define DS18B20_WRITE_SCRATCHPAD 0x4E
#define DS18B20_READ_SCRATCHPAD 0xBE
#define DS18B20_COPY_SCRATCHPAD 0x48h
#define DS18B20_RECALL_E2 0xB8
#define DS18B20_READ_POWER_SUPPLY 0xB4

typedef struct {
    OneWire *pOw;
    const uint8_t address;
} Thermometer;

Thermometer thermometer_new(OneWire *pOw, const uint8_t address);
float thermometer_readTemperatureCelsius(Thermometer*);

#endif /* TEMPERATURE_H_ */
