/*
 * display.c
 *
 *  Created on: 5 Feb 2019
 *      Author: alex
 */
#include "display.h"
#include <msp430.h>
#include "string.h"

volatile int antshow = 0;
volatile int txshow = 0;
volatile int rxshow = 0;

// LCD memory map for numeric digits
const char digit[10][2] = { { 0xFC, 0x28 }, /* "0" LCD segments a+b+c+d+e+f+k+q */
                            { 0x60, 0x20 }, /* "1" */
                            { 0xDB, 0x00 }, /* "2" */
                            { 0xF3, 0x00 }, /* "3" */
                            { 0x67, 0x00 }, /* "4" */
                            { 0xB7, 0x00 }, /* "5" */
                            { 0xBF, 0x00 }, /* "6" */
                            { 0xE4, 0x00 }, /* "7" */
                            { 0xFF, 0x00 }, /* "8" */
                            { 0xF7, 0x00 } /* "9" */
};

// LCD memory map for uppercase letters
const char alphabetBig[26][2] = { { 0xEF, 0x00 }, /* "A" LCD segments a+b+c+e+f+g+m */
                                  { 0xF1, 0x50 }, /* "B" */
                                  { 0x9C, 0x00 }, /* "C" */
                                  { 0xF0, 0x50 }, /* "D" */
                                  { 0x9F, 0x00 }, /* "E" */
                                  { 0x8F, 0x00 }, /* "F" */
                                  { 0xBD, 0x00 }, /* "G" */
                                  { 0x6F, 0x00 }, /* "H" */
                                  { 0x90, 0x50 }, /* "I" */
                                  { 0x78, 0x00 }, /* "J" */
                                  { 0x0E, 0x22 }, /* "K" */
                                  { 0x1C, 0x00 }, /* "L" */
                                  { 0x6C, 0xA0 }, /* "M" */
                                  { 0x6C, 0x82 }, /* "N" */
                                  { 0xFC, 0x00 }, /* "O" */
                                  { 0xCF, 0x00 }, /* "P" */
                                  { 0xFC, 0x02 }, /* "Q" */
                                  { 0xCF, 0x02 }, /* "R" */
                                  { 0xB7, 0x00 }, /* "S" */
                                  { 0x80, 0x50 }, /* "T" */
                                  { 0x7C, 0x00 }, /* "U" */
                                  { 0x0C, 0x28 }, /* "V" */
                                  { 0x6C, 0x0A }, /* "W" */
                                  { 0x00, 0xAA }, /* "X" */
                                  { 0x00, 0xB0 }, /* "Y" */
                                  { 0x90, 0x28 } /* "Z" */
};

void displayInit()
{
    // SETUP HARDWARE STUFF (NOT RELEVANT FOR PROJECT)
    LCDCPCTL0 = 0xFFFF;
    LCDCPCTL1 = 0xFC3F;
    LCDCPCTL2 = 0x0FFF;
    LCDCCTL0 = 0x041E;
    LCDCVCTL = 0x0208;
    LCDCCPCTL = 0x8000;

    // clear LCD
    LCDCMEMCTL |= LCDCLRM;

    // turn LCD on
    LCDCCTL0 |= LCDON;
}

/*
 * Scrolls input string across LCD screen from left to right
 */
void displayScrollText(char *msg)
{
    int length = strlen(msg);
    int oldmode = mode;
    int i;
    int s = 5;
    char buffer[6] = "      ";
    for (i = 0; i < length + 7; i++)
    {
        if (mode != oldmode)
            break;
        int t;
        for (t = 0; t < 6; t++)
            buffer[t] = ' ';
        int j;
        for (j = 0; j < length; j++)
        {
            if (((s + j) >= 0) && ((s + j) < 6))
                buffer[s + j] = msg[j];
        }
        s--;

        showChar(buffer[0], pos1);
        showChar(buffer[1], pos2);
        showChar(buffer[2], pos3);
        showChar(buffer[3], pos4);
        showChar(buffer[4], pos5);
        showChar(buffer[5], pos6);

        __delay_cycles(200000);
    }
}

void displayText(char *msg)
{
    char buffer[6] = "      ";
    int length = strlen(msg);
    int i;
    if (length > 6)
        length = 6;
    for (i = 0; i < length; i++)
        buffer[i] = msg[i];
    showChar(buffer[0], pos1);
    showChar(buffer[1], pos2);
    showChar(buffer[2], pos3);
    showChar(buffer[3], pos4);
    showChar(buffer[4], pos5);
    showChar(buffer[5], pos6);
}

/*
 * Displays input character at given LCD digit/position
 * Only spaces, numeric digits, and uppercase letters are accepted characters
 */

void showChar(char c, int position)
{
    if (c == ' ')
    {
        // Display space
        LCDMEM[position] = 0;
        LCDMEM[position + 1] = 0;
    }
    else if (c >= '0' && c <= '9')
    {
        // Display digit
        LCDMEM[position] = digit[c - 48][0];
        LCDMEM[position + 1] = digit[c - 48][1];
    }
    else if (c >= 'A' && c <= 'Z')
    {
        // Display alphabet
        LCDMEM[position] = alphabetBig[c - 65][0];
        LCDMEM[position + 1] = alphabetBig[c - 65][1];
    }
    else
    {
        // Turn all segments on if character is not a space, digit, or uppercase letter
        LCDMEM[position] = 0xFF;
        LCDMEM[position + 1] = 0xFF;
    }

    // Antenna, RX and TX symbols are multiplexed with text segments
    // and may turn off while text is rendered
    // Check if these were on and re-enable

    if (antshow)
        displayANT(1);
    if (txshow)
        displayTX(1);
    if (rxshow)
        displayRX(1);
}

/*
 * Clears memories to all 6 digits on the LCD
 */
void clearLCD()
{
    LCDMEM[pos1] = LCDBMEM[pos1] = 0;
    LCDMEM[pos1 + 1] = LCDBMEM[pos1 + 1] = 0;
    LCDMEM[pos2] = LCDBMEM[pos2] = 0;
    LCDMEM[pos2 + 1] = LCDBMEM[pos2 + 1] = 0;
    LCDMEM[pos3] = LCDBMEM[pos3] = 0;
    LCDMEM[pos3 + 1] = LCDBMEM[pos3 + 1] = 0;
    LCDMEM[pos4] = LCDBMEM[pos4] = 0;
    LCDMEM[pos4 + 1] = LCDBMEM[pos4 + 1] = 0;
    LCDMEM[pos5] = LCDBMEM[pos5] = 0;
    LCDMEM[pos5 + 1] = LCDBMEM[pos5 + 1] = 0;
    LCDMEM[pos6] = LCDBMEM[pos6] = 0;
    LCDMEM[pos6 + 1] = LCDBMEM[pos6 + 1] = 0;

    LCDM14 = LCDBM14 = 0x00;
    LCDM18 = LCDBM18 = 0x00;
    LCDM3 = LCDBM3 = 0x00;
    if (antshow)
        displayANT(1);
//    LCDMEM[12] = LCDMEM[13] = 0;
}

/* Display Battery symbol and level
 * Input: level -1,0, 1 to 6
 * -1 hides batt meter
 *  0 displays empty battery
 *  1 to 6 display the appropriate bars
 */

void displayBattery(int level)
{
    /* Turn off battery sign completely */

    LCDM18 = 0;
    LCDBM18 = 0;
    LCDM14 = 0;
    LCDBM14 = 0;

    if (level < 0)
        return;
    /* Turn on B1 */

    LCDM18 |= 0x10;
    LCDBM18 |= 0x10;

    /* Turn on BATT */

    LCDM14 |= 0x10;
    LCDBM14 |= 0x10;

    /* Turn on battery segments according to value */

    if (level >= 1)
    {
        LCDM18 |= 0x20;
        LCDBM18 |= 0x20;
    }
    if (level >= 2)
    {
        LCDM14 |= 0x20;
        LCDBM14 |= 0x20;
    }
    if (level >= 3)
    {
        LCDM18 |= 0x40;
        LCDBM18 |= 0x40;
    }
    if (level >= 4)
    {
        LCDM14 |= 0x40;
        LCDBM14 |= 0x40;
    }
    if (level >= 5)
    {
        LCDM18 |= 0x80;
        LCDBM18 |= 0x80;
    }
    if (level >= 6)
    {
        LCDM14 |= 0x80;
        LCDBM14 |= 0x80;
    }
}

// Display/hide the heart symbol

void displayHRT(int show)
{
    if (show)
    {
        LCDM3 |= 0x4;
        LCDBM3 |= 0x4;
    }
    else
    {
        LCDM3 &= ~0x4;
        LCDBM3 &= ~0x4;
    }
}

// Display/hide the timer symbol

void displayTMR(int show)
{
    if (show)
    {
        LCDM3 |= 0x8;
        LCDBM3 |= 0x8;
    }
    else
    {
        LCDM3 &= ~0x8;
        LCDBM3 &= ~0x8;
    }
}

// Display/hide the exclamation symbol

void displayEXC(int show)
{
    if (show)
    {
        LCDM3 |= 0x1;
        LCDBM3 |= 0x1;
    }
    else
    {
        LCDM3 &= ~0x1;
        LCDBM3 &= ~0x1;
    }
}

// Display/hide the record symbol

void displayREC(int show)
{
    if (show)
    {
        LCDM3 |= 0x2;
        LCDBM3 |= 0x2;
    }
    else
    {
        LCDM3 &= ~0x2;
        LCDBM3 &= ~0x2;
    }
}

// Display/hide the Antenna symbol

void displayANT(int show)
{
    if (show)
    {
        LCDM5 |= 0x4;
        LCDBM5 |= 0x4;
        antshow = 1;
    }
    else
    {
        LCDM5 &= ~0x4;
        LCDBM5 &= ~0x4;
        antshow = 0;
    }
}

// Display/hide the TX symbol

void displayTX(int show)
{
    if (show)
    {
        LCDM9 |= 0x4;
        LCDBM9 |= 0x4;
        txshow = 1;
    }
    else
    {
        LCDM9 &= ~0x4;
        LCDBM9 &= ~0x4;
        txshow = 0;
    }
}

// Display/hide the RX symbol

void displayRX(int show)
{
    if (show)
    {
        LCDM9 |= 0x1;
        LCDBM9 |= 0x1;
        rxshow = 1;
    }
    else
    {
        LCDM9 &= ~0x1;
        LCDBM9 &= ~0x1;
        rxshow = 0;
    }
}


char *temp2str(unsigned int x)
{
    static char buf[] = "   00C";
    unsigned pos = 5;
    unsigned int t = x;

    // -> 1234.5°C
    do {
        buf[--pos] = (t % 10)+48;
    } while(t /= 10);

   return buf;
}

// Displays input temperature in °C
void displayTemperature(float temp) {
    clearLCD();

    int temperature = (int)(temp * 10);

    /* negative sign */
    unsigned int isNegative = (temperature) < 0;
    if (isNegative) {
        temperature *= -1;
    }

    displayText(temp2str(temperature));

    /* comma */
    LCDM20 |= 0x01;
    LCDBM20 |= 0x01;

    /* degree */
    LCDM16 |= 0x04;
    LCDBM16 |= 0x04;

    /* minus */
    if (isNegative) {
        LCDM11 |= 0x04;
        LCDBM11 |= 0x04;
    }
    else {
        LCDM11 &= ~0x04;
        LCDBM11 &= ~0x04;
    }
}
