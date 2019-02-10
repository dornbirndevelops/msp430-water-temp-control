/*
 * bitops.h
 *
 *  Created on: 5 Feb 2019
 *      Author: alex
 */

#ifndef BITOPS_H_
#define BITOPS_H_

#define set(register, mask) register |= mask
#define clr(register, mask) register &= ~mask
#define ass(register, mask) register = mask
#define tog(register, mask) register ^= mask
#define read(register, mask) register & mask
#define bit(i) (1 << i)

#endif /* BITOPS_H_ */
