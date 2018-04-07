/*
 * display.h
 *
 *  Created on: Apr 2, 2018
 *      Author: mann53
 */

#ifndef DISPLAYDRIVER_H_
#define DISPLAYDRIVER_H_

/* function declarations*/

/* turns on the LCD */
void displayOn(void);

/* turns of the LCD */
void displayOff(void);

/* Description: Sends a string of characters to the LCD*/
void transmitDisplay(char * string);

/* clears the whole display and sets cursor back to home position */
void displayClear(void);


/* turns on the blinking cursor at home position */
void turnOnBlinkingCursor(void);

/* moves blinking cursor to left one space. The cursor needs to be turned on first before using */
void cursorLeft(void);

/* changes the display backlight brightness. Brightness parameter can be in range of 1 to 8 with 8 being the brightest setting */
void displayBrightness(int brightness);

/* 0 - 79 possible position. Each row has 15 coloumns. 0 is home position, */
void cursorPosition(int position);

void cursorHome(void);

void timeoutLED(int value);

void backspace(void);

#endif /* DISPLAYDRIVER_H_ */
