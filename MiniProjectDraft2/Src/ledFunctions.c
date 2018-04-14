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





