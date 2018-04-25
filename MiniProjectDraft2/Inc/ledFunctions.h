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

// Total number of bytes that are sent to update led strip */
#define BYTES ROWS*COLS*3

// thresholds for spectrum analyzer
#define INCREMENT 300
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

//bass threshold for mode 1
#define BASS_HIGH 2000


//Bass box max size for mode 1 ( 0-5 with 5 being the whole board and 0 a 2x2 box in the middle)
#define BOX_MAX_SIZE 5

//defines the number of colors that mode 1 cycles through for the inner box
#define NUMBER_OF_BOX_COLORS 4
#define NUMBER_OF_BACKGROUND_COLORS 4

// brightness value for all of the lights
#define BRIGHTNESS 5
#define MAX_BRIGHTNESS 100

// constants for mode 1 box size
#define LEFT_SIDE 6
#define RIGHT_SIDE 5
#define TOP_SIDE 6
#define BOTTOM_SIDE 5

/*box decay constants for how quickly the box moves in and and out */
#define BOX_DECAY_RANGE 10
#define BOX_DECAY_RATE 2

/* FUNCTION DECLARATIONS */

/* writes to the leds at low speed */
void ledStripWriteLowSpeed(struct color leds[ROWS][COLS], int bytes);

/* reorders the matrix rows that are out of place */
void ledMatrixReorder(struct color leds[ROWS][COLS]);

/* used to update led matrix and is the functio that should be used within main while loop after filtering is done */
void writeLeds(struct color leds[ROWS][COLS]);

/* sets a particular led in the matrix to a desired color */
void setColor (struct color leds[ROWS][COLS], int row, int col, int percent, int * color);

/* sets all leds in the matrix to a particular color */
void allColor (struct color leds[ROWS][COLS], int percent, int * color);

/* function for determining which colors get associated with each band */
void spectrumColor (struct color leds[ROWS][COLS], int row, int col);

/* mode for updating the led with a spectrum analyzer */
void spectrumAnalyzer(struct color leds[ROWS][COLS], int * spectrum);

/* mode 2 for generating random colors on led matrix without any music input */
void twinkle(struct color leds[ROWS][COLS]);

/* mode1 for updating leds */
void mode1(struct color leds[ROWS][COLS], int * spectrum);

/* updates the box parameters for setting the matrix colors */
void updateBoxArea(int * spectrum);

/* sets the correct color values for the led matrix in mode 1 */
void setMatrix(struct color leds[ROWS][COLS]);

#endif /* LEDFUNCTIONS_H_ */
