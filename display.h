/*
 * display.h
 *
 *  Created on: 5 Feb 2019
 *      Author: alex
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

//Change based on LCD Memory locations
#define pos1 9   /* Digit A1 begins at S18 */
#define pos2 5   /* Digit A2 begins at S10 */
#define pos3 3   /* Digit A3 begins at S6  */
#define pos4 18  /* Digit A4 begins at S36 */
#define pos5 14  /* Digit A5 begins at S28 */
#define pos6 7   /* Digit A6 begins at S14 */

// Define word access definitions to LCD memories
#ifndef LCDMEMW
#define LCDMEMW    ((int*) LCDMEM) /* LCD Memory (for C) */
#endif

extern volatile unsigned char mode;
extern const char digit[10][2];
extern const char alphabetBig[26][2];

void displayInit(void);
void displayText(char *);
void displayScrollText(char*);
void displayBattery(int);
void displayHRT(int);
void displayTMR(int);
void displayEXC(int);
void displayREC(int);
void displayANT(int);
void displayTX(int);
void displayRX(int);
void showChar(char, int);
void clearLCD(void);
void displayTemperature(float);

#endif /* DISPLAY_H_ */
