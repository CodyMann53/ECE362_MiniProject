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
		leds[row][col].red = color[0]*percent/100;
		leds[row][col].green = color[1]*percent/100;
		leds[row][col].blue = color[2]*percent/100;

	return;
}

void allColor (struct color leds[ROWS][COLS], int percent, int * color){

	for (int row = 0; row < ROWS; row++){
		for( int col = 0; col < COLS; col++){
			setColor(leds, row, col, BRIGHTNESS, color);
		}
	}
}


void setInnerBox(struct color leds[ROWS][COLS], int * color){

	int expand = 0;

	if ( boxArea >= (4 * BOX_DECAY_RANGE) ){
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

	if ( boxArea >= 0){
		// loop through each row that needs to be set
		for(int row = (BOTTOM_SIDE - expand); row <= (TOP_SIDE + expand); row++){

			//loop through each col that needs to be set for each row
			for(int col = (LEFT_SIDE + expand); col >= (RIGHT_SIDE - expand); col--){

				// set the specifice led to desired color
				setColor(leds, row, col, BRIGHTNESS, color);
			}// end of col loop
		}// end of row loop
	}
	else{

		// do nothing
	}



}

void mode1(struct color leds[ROWS][COLS], int * spectrum){

	// set every led as a base color
	allColor(leds, BRIGHTNESS, red);

	//update the box side length in the middle based on how much of a beat is present
	// this will only overwrite the area of the box that needs updating. Everything else will stay as the base color

	if (  ( (spectrum[1] > THRESH11) || (spectrum[0] > THRESH10) ) & ( (boxArea >= 4 * BOX_DECAY_RANGE) || (boxArea < 0) )  ){
		boxArea = 4 *  BOX_DECAY_RANGE;
	}
	else if (  ( (spectrum[1] > THRESH10) || (spectrum[0] > THRESH9) ) & ( (boxArea >= 4 * BOX_DECAY_RANGE) || (boxArea < 0) )  ){
		boxArea = 3 * BOX_DECAY_RANGE;

	}
	else if (  ( (spectrum[1] > THRESH9) || (spectrum[0] > THRESH8) ) & ( (boxArea >= 4 * BOX_DECAY_RANGE) || (boxArea < 0) )  ){
		boxArea = 2 * BOX_DECAY_RANGE ;

	}
	else if ( ( (spectrum[1] > THRESH8) || (spectrum[0] > THRESH7) ) & ( (boxArea >= 4 * BOX_DECAY_RANGE) || (boxArea < 0) )   ){
		boxArea = 1 * BOX_DECAY_RANGE;

	}
	else{

		if (boxArea >= 0){

			// decrease box area
			boxArea = boxArea - BOX_DECAY_RATE;
		}

	}

		// update the inner box
		setInnerBox(leds, blue);
}

void spectrumColor (struct color leds[ROWS][COLS], int row, int col){

	// loop through all of the rows that need to be set
	for (int x = 0; x < row; x++){

		// if else clause to determine which colors get associated with each frequency band
		if( (col == 0) || (col == 1) ){
			setColor(leds, x, col, BRIGHTNESS, red);
		}
		else if( (col == 2) || (col==3) ){
			setColor(leds, x, col, BRIGHTNESS, blue);
		}
		else if( (col == 4) || (col==5) ){
			setColor(leds, x, col, BRIGHTNESS, magenta);
		}
		else if( (col == 6) || (col==7) ){
			setColor(leds, x, col, BRIGHTNESS, green);
		}
		else if( (col == 8) || (col==9) ){
			setColor(leds, x, col, BRIGHTNESS, yellow);
		}
		else if( (col == 10) || (col==11) ){
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

void twinkle(struct color leds[ROWS][COLS])
{
  int fade = MAX_BRIGHTNESS;
  int fadeFlag = 0;
  int red = 255;
  int rFlag = 0;
  int green = 255;
  int gFlag = 0;
  int blue = 255;
  int bFlag = 0;
  int sub;
  int val;
  int start[3];
  for(int row = 0; row < ROWS; row++){
      for(int col = 0; col < COLS; col++){
          //initializes the colors for each led
          start[0] = red;
          start[1] = green;
          start[2] = blue;

          setColor(leds, row, col, fade, start);

          //varies the brightness for
          if(fadeFlag != 1){
             fade -= 5;
          }
          else{
              fade += 5;
          }
          if(fade < 50){
              fadeFlag = 1;
          }
          if(fade == 100)
          {
              fadeFlag = 0;
          }

          //creates a random value to be subtracted from red
          sub = (rand() + 50)%(100+1);
          red -= sub;

          //keeps it in warm color range
          if(red < 140){
              red = 255;
          }

          //creates a random value to be subtracted from green
          sub = (rand() + 50)%(100+1);
          green -= sub;

          //keeps it in warm color range
          if(green < 140){
              green = 255;
          }

          //creates a random value to be subtracted from blue
          sub = (rand() + 50)%(100+1);
          blue -= sub;

          //keeps it in warm color range
          if(blue < 140){
              blue = 255;
          }
      }
  }

}
