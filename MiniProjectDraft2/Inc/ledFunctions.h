/*
 * ledFunctions.h
 *
 *  Created on: Apr 7, 2018
 *      Author: Cody Mann
 */

#ifndef LEDFUNCTIONS_H_
#define LEDFUNCTIONS_H_

/* MACRO DEFINITIONS */
struct color{
	char green;
	char red;
	char blue;
}color;

/* Number of leds being written to. */
#define ROWS 12
#define COLS 12

#define THRESH1 25
#define THRESH2 50
#define THRESH3 75
#define THRESH4 100
#define THRESH5 125
#define THRESH6 150

#define START 3
#define END (START + 7)

#define BRIGHTNESS 50

/* Total number of bytes that are sent to update led strip */
#define BYTES ROWS*COLS*3

/* FUNCTION DECLARATIONS */

void setColor (struct color leds[ROWS][COLS], int row, int col, int percent, int * color);

void allColor (struct color leds[ROWS][COLS], int percent, int * color);

void mode1(struct color leds[ROWS][COLS], int * spectrum);

void spectrumColor (struct color leds[ROWS][COLS], int row, int col);

void spectrumAnalyzer(struct color leds[ROWS][COLS], int * spectrum);

void ledStripWriteLowSpeed(struct color leds[ROWS][COLS], int bytes);

#endif /* LEDFUNCTIONS_H_ */
