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

void setBorderColor(struct color leds[ROWS][COLS], int * color, int depth){
	//variable initializations
	int col = 0;
	int row = 0;


	for ( int x = 0; x <= depth; x++){

		/* top and bottom */
		// setting bottom border (0:depth, 0: COLS - depth - 1
		for( col = depth; col < COLS; col++){
			setColor(leds, x, col, BRIGHTNESS, color);
		}

		// setting top border
		for( col = 0; col < COLS; col++){
			setColor(leds, 11 - x, col, BRIGHTNESS, color);
		}

		/* sides */
		// setting left side border
		for (row = 0; row < ROWS; row++){
			setColor(leds, row, 11 - x, BRIGHTNESS, color);
		}

		// setting right side border
		for (row = 0; row < ROWS; row++){
			setColor(leds, row, x, BRIGHTNESS, color);
		}
	}




}

void setInnerBoxColor(struct color leds[ROWS][COLS], int * color, int depth){

	// set inner box based on how far in the border is
	for (int row = (depth + 1); row < (ROWS - 1 - depth); row++){
		for (int col = (depth + 1); col < (COLS - 1 - depth); col++){
			setColor (leds, row, col, BRIGHTNESS, color);
		}
	}
}

void mode1(struct color leds[ROWS][COLS], int * spectrum){

	// variable initializations
	int depth = 1;

	//reset the border based on spectrum 3
	if ( spectrum[BORDER_SPECTRUM] > THRESH6){
		setBorderColor(leds, magenta, depth);
	}
	else if( spectrum[BORDER_SPECTRUM] > THRESH5){
		setBorderColor(leds, green, depth);
	}
	else if (spectrum[BORDER_SPECTRUM] > THRESH4){
		setBorderColor(leds, red, depth);
	}
	else if (spectrum[BORDER_SPECTRUM] > THRESH3){
		setBorderColor(leds, blue, depth);
	}


	if ( (spectrum[0] > 100) || (spectrum[1] > 100) ){

		if (spectrum[4] > 100){
			setInnerBoxColor(leds, red, depth);
		}
		else if( spectrum[5] > 100){
			setInnerBoxColor(leds, blue, depth);
		}
		else{
			setInnerBoxColor(leds, green, depth);
		}
	}
	else{
		setInnerBoxColor(leds, off, depth);
	}
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
