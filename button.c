/*
 * button.c
 *
 *  Created on: 5 Feb 2019
 *      Author: alex
 */
#include "button.h"
#include "types.h"
#include "bitops.h"

#include <msp430.h>

static buttonPressHandler _pressHandlers[] = { NULL, NULL };
static int _buttonPinMap[] = { 1, 2 };

void button_new(eButton btn, buttonPressHandler action)
{
    unsigned int pin = _buttonPinMap[btn];
    if (_pressHandlers[btn] == NULL)
    {
        clr(P1DIR, bit(pin));
        set(P1OUT, bit(pin));
        set(P1REN, bit(pin));
        set(P1IES, bit(pin));
        clr(P1IFG, bit(pin));
        clr(P1IE, bit(pin));
    }
    _pressHandlers[btn] = action;
    set(P1IE, bit(pin));
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void button_isr(void)
{
    unsigned int i = BUTTON_AMOUNT;

    while (i-- > 0)
    {
        unsigned int pin = _buttonPinMap[i];
        if (P1IFG & bit(pin))
        {
            if (_pressHandlers[i])
            {
                _pressHandlers[i]();
            }
            clr(P1IFG, bit(pin));
        }
    }

    P1IFG = 0;
}
