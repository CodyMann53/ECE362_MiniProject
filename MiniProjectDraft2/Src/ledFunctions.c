/*
 * ledFunctions.c
 *
 *  Created on: Apr 7, 2018
 *      Author: Andrew Osborne
 */

/* INCLUDES */
#include "ledFunctions.h"
#include "globalVariables.h"

/* FUNCTION DEFINITIONS */

void writeLeds(struct color leds[ROWS][COLS]){

	// reorder out of place rows
	ledMatrixReorder(leds);

	//write to the leds
	ledMatrixReorder(leds);
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

void mode1(struct color leds[ROWS][COLS], int * spectrum){

	if ( (spectrum[0] > 100) || (spectrum[1] > 100)){

		if (spectrum[4] > 100){
			allColor(leds, BRIGHTNESS, blue);
		}
		else if( spectrum[5] > 100){
			allColor(leds, BRIGHTNESS, red);
		}
		else{
			allColor(leds, BRIGHTNESS, green);
		}
	}
	else{
		allColor(leds, BRIGHTNESS, off);
	}
}

void spectrumColor (struct color leds[ROWS][COLS], int row, int col){
	int color[3] = {0,0,0};
	for (int x = 0; x < row; x++){
		if(col == START)
		{
			color[0] = 0;
			color[1] = 0;
			color[2] = 255;
		}
		else if(col == START+1)
		{
			color[0] = 0;
			color[1] = 255;
			color[2] = 0;
		}
		else if(col == START+2)
		{
			color[0] = 255;
			color[1] = 0;
			color[2] = 0;
		}
		else if(col == START+3)
		{
			color[0] = 255;
			color[1] = 255;
			color[2] = 255;
		}
		else if(col == START+4)
		{
			color[0] = 0;
			color[1] = 255;
			color[2] = 255;
		}
		else if(col == START+5)
		{
			color[0] = 255;
			color[1] = 0;
			color[2] = 255;
		}
		else if(col == START+6)
		{
			color[0] = 125;
			color[1] = 125;
			color[2] = 125;
		}
		setColor(leds, x, col, BRIGHTNESS, color);
	}
}

void spectrumAnalyzer(struct color leds[ROWS][COLS], int * spectrum){

	//reset all of the leds to off
	allColor(leds, BRIGHTNESS, off);

	// start at highest frequency band
	int x = 6;

	// cycle through all led array columns
	for( int col = START; col < END; col++){

		// go though all of the frequency bands (6-0)
		if ( x >= 0){

			if(spectrum[x] > THRESH6){
				spectrumColor(leds, 6, col);
			}
			else if(spectrum[x] > THRESH5){
				spectrumColor(leds, 5, col);
			}
			else if(spectrum[x] > THRESH4){
				spectrumColor(leds, 4, col);
			}
			else if(spectrum[x] > THRESH3){
				spectrumColor(leds, 3, col);
			}
			else if(spectrum[x] > THRESH2){
				spectrumColor(leds, 2, col);
			}
			else if (spectrum[x] > THRESH1){
				spectrumColor(leds, 1, col);
			}
			else{
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




