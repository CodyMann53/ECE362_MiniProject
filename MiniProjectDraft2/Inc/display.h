/*
 * display.h
 *
 *  Created on: Apr 2, 2018
 *      Author: mann53
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

/* macro declarations */


/* function declarations*/

void displayOn(void);

void displayOff(void);

void transmitDisplay(char * string);

void displayClear(void);

void turnOnBlinkingCursor(void);

void cursorLeft(void);

void displayBrightness(int brightness);

/* 0 - 79 possible position. Each row has 15 coloumns */
void cursorPosition(int position);

void cursorHome(void);

void timeoutLED(int value);

void backspace(void);

#endif /* DISPLAY_H_ */
