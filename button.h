/*
 * button.h
 *
 *  Created on: 5 Feb 2019
 *      Author: alex
 */

#ifndef BUTTON_H_
#define BUTTON_H_

typedef enum
{
    BUTTON_LEFT, BUTTON_RIGHT, BUTTON_AMOUNT
} eButton;
typedef void (*buttonPressHandler)(void);

void button_new(eButton, buttonPressHandler);

#endif /* BUTTON_H_ */
