/*
 * onewire.h
 *
 *  Created on: 8 Feb 2019
 *      Author: alex
 */

#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#include <stdint.h>

/*
 * Perform a 1-Wire reset cycle.
 */
void onewire_reset();

uint8_t onewire_readByte();
void onewire_writeByte(uint8_t);

uint8_t onewire_read8();
uint16_t onewire_read16();
uint32_t onewire_read32();
uint64_t onewire_read64();

void onewire_write8(uint8_t);
void onewire_write16(uint16_t);
void onewire_write32(uint32_t);
void onewire_write64(uint64_t);

#endif /* ONEWIRE_H_ */
