/*
 * delay.h
 *
 *  Created on: 9 Feb 2019
 *      Author: alex
 */

#ifndef DELAY_H_
#define DELAY_H_

#include <msp430.h>

#define CYCLES_PER_US 1L // depends on the CPU speed
#define CYCLES_PER_MS (CYCLES_PER_US * 1000L)

#define DELAY_US(x) __delay_cycles((x * CYCLES_PER_US))
#define DELAY_MS(x) __delay_cycles((x * CYCLES_PER_MS))

#endif /* DELAY_H_ */
