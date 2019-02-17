/*
 * pump.h
 *
 *  Created on: 17 Feb 2019
 *      Author: alex
 */

#ifndef PUMP_H_
#define PUMP_H_

typedef enum { PUMP_OFF, PUMP_ON } ePumpState;

void setPumpState(ePumpState state);

#endif /* PUMP_H_ */
