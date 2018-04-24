/*
 * ledFunctions.c
 *
 *  Created on: Apr 7, 2018
 *      Author: Andrew Osborne
 */

/* INCLUDES */
#include "ledFunctions.h"
#include "globalVariables.h"
#include "stm32f0xx_hal.h"

/* FUNCTION DEFINITIONS */

void writeLeds(struct color leds[ROWS][COLS]){

	// reorder out of place rows
	ledMatrixReorder(leds);

	// disable interrupts
	__disable_irq();

	//write to the leds
	ledStripWriteLowSpeed(leds, BYTES);

	//enable interrupts
	__enable_irq();
}

void ledMatrixReorder(struct color leds[ROWS][COLS]){

	struct color ledsTmp[COLS];

	// loop through every other row.
	for( int row = 1; row < ROWS; row+= 2){

		// flip the current row into a temporary array
		for ( int col = 0; col < COLS; col++){
			ledsTmp[col] = leds[row][COLS-col-1];
		}

		// update the the row that is out of order using the flipped array
		for (int col = 0; col < COLS; col++){
			leds[row][col] = ledsTmp[col];
		}
	}
}

void setColor (struct color leds[ROWS][COLS], int row, int col, int percent, int * color)
{
		//set the red, green, and blue colors to a percentage brightness
		leds[row][col].red = color[0] * percent / 100;
		leds[row][col].green = color[1] * percent / 100;
		leds[row][col].blue = color[2] * percent / 100;

	return;
}

void allColor(struct color leds[ROWS][COLS], int percent, int * color){

	for (int row = 0; row < ROWS; row++){
		for( int col = 0; col < COLS; col++){
			setColor(leds, row, col, percent, color);
		}
	}
}

void setMatrix(struct color leds[ROWS][COLS], int * spectrum){

	/* CHECKING SPECTRUM TO SET THE BOX AREA */

	//sample
	bassCurrent = spectrum[0];

	// if any of the base spectrums are above the set threshold, then set the box to the max size and allow the decay back in to start
	if ( (bassCurrent > BASS_THRESH) & (bassPrevious < 500) ){
		boxArea = BOX_MAX_SIZE *  BOX_DECAY_RANGE;
	}
	else{// if the base spectrums didn't not get above threshold, then keep on decaying back to the middle

		if (boxArea >= 0){// if the box area is still present on board, then keep bringing it back in. Box will go away when box area gets to -1

			// decrease box area
			boxArea = boxArea - BOX_DECAY_RATE;

		}
		else{// box came all the way back in

			// increment color if box came all the way back in
			colorIndex = colorIndex + 1;

			// keep color index from 0-8
			if (colorIndex > NUMBER_OF_BOX_COLORS - 1){

				//reset back to first color
				colorIndex = 0;
			}
		}
	}

	//updating the bass current and bass previous
	bassPrevious = bassCurrent;

	/* UPDATING THE LED MATRIX BASED BOX'S CURRENT AREA */

	// expand is set to a value based on how much the box has decayed back in and used to update the led matrix
	int expand = 0;

	if ( boxArea >= 5 * BOX_DECAY_RANGE){
		expand = 5;
	}
	if ( boxArea >= 4 * BOX_DECAY_RANGE){
		expand = 4;
	}
	else if ( boxArea >= 3 * BOX_DECAY_RANGE){
		expand = 3;
	}
	else if ( boxArea >= 2 * BOX_DECAY_RANGE){
		expand = 2;
	}
	else if ( boxArea >= 1 * BOX_DECAY_RANGE){
		expand = 1;
	}
	else if ( boxArea >= 0 * BOX_DECAY_RANGE){
		expand = 0;
	}
	else{
		expand = -1;
	}

	// as long as the box area is greater than or equal to 0, the box is still decaying and needs to be updated on the led matrix
	if ( (boxArea >= 0 ) & (expand >=0) ){

		// loop through each row that needs to be set
		for(int row = 0; row < ROWS; row++){

			//loop through each column that needs to be set for each row
			for(int col = 0; col < COLS; col++){

				// if inside the box range set the box color
				if(  ( col >= (RIGHT_SIDE - expand) )  && ( col <= LEFT_SIDE + expand) && (row <= TOP_SIDE + expand) && (row >= BOTTOM_SIDE - expand) ){

					setColor(leds, row, col, BRIGHTNESS, yellow);
				}
				else{// set the background color

					setColor(leds, row, col, BRIGHTNESS, red);

				}
			}
		}
	}
	else{
		allColor(leds, BRIGHTNESS, red);
	}


}

void mode1(struct color leds[ROWS][COLS], int * spectrum){

	// update the matrix
	setMatrix(leds, spectrum);
}

void spectrumColor (struct color leds[ROWS][COLS], int row, int col){

	// loop through all of the rows that need to be set
	for (int x = 0; x < row; x++){

		// if else clause to determine which colors get associated with each frequency band
		if( (col == 0) || (col == 1) ){ // 6th band
			setColor(leds, x, col, BRIGHTNESS, red);
		}
		else if( (col == 2) || (col==3) ){ // 5th band
			setColor(leds, x, col, BRIGHTNESS, blue);
		}
		else if( (col == 4) || (col==5) ){// 4th band
			setColor(leds, x, col, BRIGHTNESS, magenta);
		}
		else if( (col == 6) || (col==7) ){// 3rd band
			setColor(leds, x, col, BRIGHTNESS, green);
		}
		else if( (col == 8) || (col==9) ){// 2nd band
			setColor(leds, x, col, BRIGHTNESS, yellow);
		}
		else if( (col == 10) || (col==11) ){// 1st band
			setColor(leds, x, col, BRIGHTNESS, teal);
		}
	}
}

void spectrumAnalyzer(struct color leds[ROWS][COLS], int * spectrum){

	//reset all of the leds to off
	allColor(leds, BRIGHTNESS, off);

	// start at second to highest frequency band
	int x = 5;

	// cycle through all led array columns
	for( int col = 0; col < COLS; col+=2){

		// go though all of the frequency bands (6-0)
		if ( x >= 0){
			if(spectrum[x] > THRESH11){ // threshold 11

				// set two columns corresponding to the particular band
				// at the given threshold
				spectrumColor(leds, 11, col);
				spectrumColor(leds, 11, col + 1);
			}
			else if(spectrum[x] > THRESH10){// threshold 10

				// set two columns corresponding to the particular band
				// at the given threshold
				spectrumColor(leds, 10, col);
				spectrumColor(leds, 10, col + 1);
			}
			else if(spectrum[x] > THRESH9){// threshold 9

				// set two columns corresponding to the particular band
				// at the given threshold
				spectrumColor(leds, 9, col);
				spectrumColor(leds, 9, col + 1);
			}
			else if(spectrum[x] > THRESH8){// threshold 8

				// set two columns corresponding to the particular band
				// at the given threshold
				spectrumColor(leds, 8, col);
				spectrumColor(leds, 8, col + 1);
			}
			else if(spectrum[x] > THRESH7){// threshold 7

				// set two columns corresponding to the particular band
				// at the given threshold
				spectrumColor(leds, 7, col);
				spectrumColor(leds, 7, col + 1);
			}
			else if(spectrum[x] > THRESH6){// threshold 6

				// set two columns corresponding to the particular band
				// at the given threshold
				spectrumColor(leds, 6, col);
				spectrumColor(leds, 6, col + 1);
			}
			else if(spectrum[x] > THRESH5){// threshold 5

				// set two columns corresponding to the particular band
				// at the given threshold
				spectrumColor(leds, 5, col);
				spectrumColor(leds, 5, col + 1);
			}
			else if(spectrum[x] > THRESH4){// threshold 4

				// set two columns corresponding to the particular band
				// at the given threshold
				spectrumColor(leds, 4, col);
				spectrumColor(leds, 4, col + 1);
			}
			else if(spectrum[x] > THRESH3){// threshold 3

				// set two columns corresponding to the particular band
				// at the given threshold
				spectrumColor(leds, 3, col);
				spectrumColor(leds, 3, col + 1);
			}
			else if(spectrum[x] > THRESH2){// threshold 2

				// set two columns corresponding to the particular band
				// at the given threshold
				spectrumColor(leds, 2, col);
				spectrumColor(leds, 2, col + 1);
			}
			else if(spectrum[x] > THRESH1){// threshold 1

				// set two columns corresponding to the particular band
				// at the given threshold
				spectrumColor(leds, 1, col);
				spectrumColor(leds, 1, col + 1);
			}
			else{// no threshold met so only light frist row
				spectrumColor(leds, 0, col);
			}
		}

		// move down a frequency band
		x--;
	}
}

void twinkle(struct color leds[ROWS][COLS]){
	// will be written by Fyffe
}
