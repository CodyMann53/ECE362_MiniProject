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
#define THRESH2  50
#define THRESH3 75
#define THRESH4 100
#define THRESH5 125
#define THRESH6 150

#define START 3
#define END (START + 7)

#define BRIGHTNESS 40

/* Total number of bytes that are sent to update led strip */
#define BYTES ROWS*COLS*3

/* FUNCTION DECLARATIONS */

/* Updates the LED strip. Data parameter is an array of colors
and numBytes is the number of bytes that needs to be written to the LED strip with 3 bytes per LED. */
void ledStripWrite(struct color colors[ROWS][COLS], int numBytes);

/* Sets a certain position in the colors array to white with percent brightness. */
void setWhite (struct color colors[ROWS][COLS], int row, int col, int percent);

/* Sets a certain position in the colors array to off.*/
void setOff (struct color colors[ROWS][COLS], int row, int col);

/* Sets a certain position in the colors array to blue with percent brightness. */
void setBlue (struct color colors[ROWS][COLS], int row, int col, int percent);

/* Sets a certain position in the colors array to red with percent brightness. */
void setRed (struct color colors[ROWS][COLS], int row, int col, int percent);

/* Sets a certain position in the colors array to green with percent brightness. */
void setGreen (struct color colors[ROWS][COLS], int row, int col, int percent);

/* Sets a certain position in the colors array to any color with percent brightness. */
void setColor (struct color colors[ROWS][COLS], int row, int col, int percent, int * color1);

/* Sets all of the LEDS green. */
void allGreen (struct color colors[ROWS][COLS], int percent);

/* Sets all of the LEDS red. */
void allRed (struct color colors[ROWS][COLS], int percent);

/* Sets all of the leds white. */
void allWhite(struct color colors[ROWS][COLS], int percent);

/* Sets all of the leds blue. */
void allBlue(struct color colors[ROWS][COLS], int percent);

void allOff(struct color colors[ROWS][COLS]);

/* Mode one of how leds get updated based on audio input signal */
void mode1(struct color colors[ROWS][COLS], int * spectrum);

/* Frequency spectrum is red */
void spectrumColor (struct color colors[ROWS][COLS], int row, int col);

/* used as a mode for spectrum analyzing */
void spectrumAnalyzer(struct color colors[ROWS][COLS], int * spectrum);

#endif /* LEDFUNCTIONS_H_ */
