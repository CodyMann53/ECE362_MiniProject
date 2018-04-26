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
#include "tim.h"
#include "stdlib.h"

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

void updateBoxArea(int * spectrum){

	/* CHECKING SPECTRUM TO SET THE BOX AREA */

		//sample
		bassCurrent = spectrum[0];

		// keep a sum of all the bass values and count as a sample
		bassMovingAverage = bassMovingAverage + bassCurrent;
		bassSampleCount += 1;

		// if the desired number of samples have been taken
		if (bassSampleCount > SAMPLES){

			// take a moving average of all the bass values
			bassThresh = bassMovingAverage / SAMPLES;

			// reset the count back to zero
			bassSampleCount = 0;

		}

		// if any of the base spectrums are above the set threshold, then set the box to the max size and allow the decay back in to start
		if ( (bassCurrent > bassThresh) & (bassPrevious < bassThresh - BASS_THRESH_DIFF) ){

			// set increment box color flag
			incrementBoxColorFlag = 1;

			// set to maximum box size
			boxArea = BOX_MAX_SIZE *  BOX_DECAY_RANGE;

		}
		else{// if the base spectrums didn't not get above threshold, then keep on decaying back to the middle

			if (boxArea >= 0){// if the box area is still present on board, then keep bringing it back in. Box will go away when box area gets to -1

				// decrease box area
				boxArea = boxArea - BOX_DECAY_RATE;

			}
			else{// box came all the way back in

				// increment color if box came all the way back in

				// only increment color if there was no beat
				if ( (boxArea < 0) & (boxAreaPrevious < 0) &  (incrementBoxColorFlag == 1) ){

					// clear increment Box Color flag
					incrementBoxColorFlag = 0;

					// move to the next box color
					colorIndex = colorIndex + 1;
				}


				// keep color index from 0-8
				if (colorIndex > (NUMBER_OF_BOX_COLORS - 1) ){

					// set increment background color flag once the box colors have cycled all the way through
					incrementBackgroundColor = 1;

					//reset back to first color
					colorIndex = 0;

				}
			}
		}

		//updating bass spectrum and box area memory
		bassPrevious = bassCurrent;
		boxAreaPrevious = boxArea;

}

void setMatrix(struct color leds[ROWS][COLS]){

	/* UPDATING THE LED MATRIX BASED BOX'S CURRENT AREA */

	// expand is set to a value based on how much the box has decayed back in and used to update the led matrix
	int expand = 0;

	if ( boxArea >= (BOX_MAX_SIZE - 1) * BOX_DECAY_RANGE){
		expand = 5;
	}
	if ( boxArea >= 3 * BOX_DECAY_RANGE){
		expand = 4;
	}
	else if ( boxArea >= 2 * BOX_DECAY_RANGE){
		expand = 3;
	}
	else if ( boxArea >= 1 * BOX_DECAY_RANGE){
		expand = 2;
	}
	else if ( boxArea >= 0 * BOX_DECAY_RANGE){
		expand = 1;
	}
	else{

		expand = -1;
	}

	// loop through each row that needs to be set
	for(int row = 0; row < ROWS; row++){

		//loop through each column that needs to be set for each row
		for(int col = 0; col < COLS; col++)

			// if inside the box range set the box color
			if(  ( col >= (RIGHT_SIDE - expand) )  && ( col <= LEFT_SIDE + expand) && (row <= TOP_SIDE + expand) && (row >= BOTTOM_SIDE - expand) && (expand >= 0)){

				setColor(leds, row, col, brightness, mode1BoxColorPattern[colorIndex] );
			}
			else{// set the background color

				setColor(leds, row, col, brightness, mode1BackgroundColorPattern[backgroundColorIndex]);
			}
	}

	// if increment background flag has been set
	if (incrementBackgroundColor == 1){

		// clear increment background color
		incrementBackgroundColor = 0;

		//update to the next background color
		backgroundColorIndex = backgroundColorIndex + 1;

		// make sure background color index is in range
		if ( backgroundColorIndex > (NUMBER_OF_BACKGROUND_COLORS - 1) ){

			// reset the background color index back to the starting point
			backgroundColorIndex = 0;
		}
	}
}

void mode1(struct color leds[ROWS][COLS], int * spectrum){

	//udpate box area
	updateBoxArea(spectrum);

	// set the matrix colors
	setMatrix(leds);

}

void spectrumColor (struct color leds[ROWS][COLS], int row, int col){

	// loop through all of the rows that need to be set
	for (int x = 0; x < row; x++){

		// if else clause to determine which colors get associated with each frequency band
		if( (col == 0) || (col == 1) ){ // 6th band
			setColor(leds, x, col, brightness, red);
		}
		else if( (col == 2) || (col==3) ){ // 5th band
			setColor(leds, x, col, brightness, blue);
		}
		else if( (col == 4) || (col==5) ){// 4th band
			setColor(leds, x, col, brightness, magenta);
		}
		else if( (col == 6) || (col==7) ){// 3rd band
			setColor(leds, x, col, brightness, green);
		}
		else if( (col == 8) || (col==9) ){// 2nd band
			setColor(leds, x, col, brightness, yellow);
		}
		else if( (col == 10) || (col==11) ){// 1st band
			setColor(leds, x, col, brightness, teal);
		}
	}
}

void spectrumAnalyzer(struct color leds[ROWS][COLS], int * spectrum){

	//reset all of the leds to off
	allColor(leds, brightness, off);

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
				spectrumColor(leds, 0, col + 1);
			}
		}

		// move down a frequency band
		x--;
	}
}

void twinkle(struct color leds[ROWS][COLS]){

  static int red = 255;
  static int green = 140;
  static int blue = 100;
  static int start[3];
  static int sub1 = 0;
  static int sub2 = 0;
  static int sub3 = 0;
  static int count = 0;
  start[0] = red;
  start[1] = green;
  start[2] = blue;
  allColor(leds, brightness, start);
  allColor(leds, brightness, off);
  count++;
  if(msCount > 50)
  {
      msCount = 0;
      fade = fade + fadeAmount;
      if(fade <= 5 || fade >= brightness)
      {
              fadeAmount *= -1;
      }
  }
  for(int row = 0; row < 12; row++)
  {
      for(int col = 0; col < 12; col++)
      {
          //initializes the colors for each led
          red += sub1;
          blue += sub2;
          green += sub3;
          start[0] = red;
          start[1] = green;
          start[2] = blue;
          setColor(leds, row, col, fade, start);
                   //creates a random value to be subtracted from red
          sub1 = (rand() + 0)%(5+1);
          sub1 *= -1;

                   //keeps it in warm color range
          if(red < 140){
              red = 255;
          }
          //creates a random value to be subtracted from green
          sub2 = (rand() + 0)%(5+1);
          sub2 *= -1;

          //keeps it in warm color range
          if(green < 100){
              green = 140;
          }
          //creates a random value to be subtracted from blue
          sub3 = (rand() + 0)%(5+1);
          sub3 *= -1;

          //keeps it in warm color range
          if(blue < 50){
              blue = 100;
          }
       }
   }
}
