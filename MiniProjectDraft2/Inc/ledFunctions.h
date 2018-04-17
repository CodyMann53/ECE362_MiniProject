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

/* which the spectrum the border color is with respect to */
#define BORDER_SPECTRUM 3

// thresholds for spectrum analyzer
#define INCREMENT 10
#define THRESH1 INCREMENT
#define THRESH2 THRESH1 + INCREMENT
#define THRESH3 THRESH2 + INCREMENT
#define THRESH4 THRESH3 + INCREMENT
#define THRESH5 THRESH4 + INCREMENT
#define THRESH6 THRESH5 + INCREMENT
#define THRESH7 THRESH6 + INCREMENT
#define THRESH8 THRESH7 + INCREMENT
#define THRESH9 THRESH8 + INCREMENT
#define THRESH10 THRESH9 + INCREMENT
#define THRESH11 THRESH10 + INCREMENT

// brightness value for all of the lights
#define BRIGHTNESS 75
#define MAX_BRIGHTNESS 100

// Total number of bytes that are sent to update led strip */
#define BYTES ROWS*COLS*3

/* FUNCTION DECLARATIONS */

/* sets a particular led in the matrix to a desired color */
void setColor (struct color leds[ROWS][COLS], int row, int col, int percent, int * color);

/* sets all leds in the matrix to a particular color */
void allColor (struct color leds[ROWS][COLS], int percent, int * color);

/* mode1 for updating leds */
void mode1(struct color leds[ROWS][COLS], int * spectrum);

/* function for determining which colors get associated with each band */
void spectrumColor (struct color leds[ROWS][COLS], int row, int col);

/* mode for updating the led with a spectrum analyzer */
void spectrumAnalyzer(struct color leds[ROWS][COLS], int * spectrum);

void ledStripWriteLowSpeed(struct color leds[ROWS][COLS], int bytes);

/* reorders the matrix rows that are out of place */
void ledMatrixReorder(struct color leds[ROWS][COLS]);

/* used to update led matrix and is the functio that should be used within main while loop after filtering is done */
void writeLeds(struct color leds[ROWS][COLS]);

/* mode 2 for generating random colors on led matrix without any music input */
void twinkle(struct color leds[ROWS][COLS]);

/* sets the border of the led matrix to a certain color and also the depth that it goes in.
 * If only the outside border is required, then depth is 0 */
void setBorderColor(struct color leds[ROWS][COLS], int * color, int depth);

/* sets the inside of the border based on the settings of setBorderColor function */
void setInnerBoxColor(struct color leds[ROWS][COLS], int * color, int depth);

#endif /* LEDFUNCTIONS_H_ */
