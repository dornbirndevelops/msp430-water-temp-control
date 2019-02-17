/*
 * thermometer.h
 *
 *  Created on: 13 Feb 2019
 *      Author: alex
 */

#ifndef THERMOMETER_H_
#define THERMOMETER_H_

#include <stdint.h>

typedef uint64_t deviceaddress_t;

deviceaddress_t thermometer_getAddress(); // only works on single connected devices
void thermometer_getTemperaturesC(float * const temperatures,
                                  deviceaddress_t const * const devices,
                                  uint16_t count);

#endif /* THERMOMETER_H_ */
