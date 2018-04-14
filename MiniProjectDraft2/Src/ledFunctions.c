/*
 * ledFunctions.c
 *
 *  Created on: Apr 7, 2018
 *      Author: Andrew Osborne
 */

/* INCLUDES */
#include "ledFunctions.h"

/* FUNCTION DEFINITIONS */

void setWhite (struct color colors[ROWS][COLS], int row, int col, int percent)
{
		colors[row][col].green = 255*percent/100;
		colors[row][col].red = 255*percent/100;
		colors[row][col].blue = 255*percent/100;

	return;
}

void setOff (struct color colors[ROWS][COLS], int row, int col)
{
		colors[row][col].green = 0;
		colors[row][col].red = 0;
		colors[row][col].blue = 0;

	return;
}

void setBlue (struct color colors[ROWS][COLS], int row, int col, int percent)
{
		colors[row][col].green = 0;
		colors[row][col].red = 0;
		colors[row][col].blue = 255*percent/100;

	return;
}

void setRed (struct color colors[ROWS][COLS], int row, int col, int percent)
{
		colors[row][col].green = 0;
		colors[row][col].red = 255*percent/100;
		colors[row][col].blue = 0;

	return;
}

void setGreen (struct color colors[ROWS][COLS], int row, int col, int percent)
{
		colors[row][col].green = 255*percent/100;
		colors[row][col].red = 0;
		colors[row][col].blue = 0;

	return;
}

void setColor (struct color colors[ROWS][COLS], int row, int col, int percent, int * color1)
{
		colors[row][col].green = color1[0]*percent/100;
		colors[row][col].red = color1[1]*percent/100;
		colors[row][col].blue = color1[2]*percent/100;

	return;
}

void allGreen (struct color colors[ROWS][COLS], int percent){

	for (int row = 0; row < ROWS; row++){
		for( int col = 0; col < COLS; col++){
			setGreen(colors, row, col, percent);
		}
	}
}

void allRed (struct color colors[ROWS][COLS], int percent){

	for (int row = 0; row < ROWS; row++){
		for( int col = 0; col < COLS; col++){
			setRed(colors, row, col, percent);
		}
	}
}

void allBlue (struct color colors[ROWS][COLS], int percent){

	for (int row = 0; row < ROWS; row++){
		for( int col = 0; col < COLS; col++){
			setBlue(colors, row, col, percent);
		}
	}
}

void allWhite (struct color colors[ROWS][COLS], int percent){

	for (int row = 0; row < ROWS; row++){
		for( int col = 0; col < COLS; col++){
			setWhite(colors, row, col, percent);
		}
	}
}

void allOff (struct color colors[ROWS][COLS]){

	for (int row = 0; row < ROWS; row++){
		for( int col = 0; col < COLS; col++){
			setOff(colors, row, col);
		}
	}
}

void mode1(struct color colors[ROWS][COLS], int * spectrum){

	if ( (spectrum[0] > 100) || (spectrum[1] > 100)){

		if (spectrum[4] > 100){
			allGreen(colors, BRIGHTNESS);
		}
		else if( spectrum[5] > 100){
			allBlue(colors, BRIGHTNESS);
		}
		else{
			allRed(colors, BRIGHTNESS);
		}
	}
	else{
		allOff(colors);
	}
}


void spectrumColor (struct color colors[ROWS][COLS], int row, int col){
	int color1[3] = {0,0,0};
	for (int x = 0; x < row; x++){
		if(col == START)
		{
			color1[0] = 0;
			color1[1] = 0;
			color1[2] = 255;
		}
		else if(col == START+1)
		{
			color1[0] = 0;
			color1[1] = 255;
			color1[2] = 0;
		}
		else if(col == START+2)
		{
			color1[0] = 255;
			color1[1] = 0;
			color1[2] = 0;
		}
		else if(col == START+3)
		{
			color1[0] = 255;
			color1[1] = 255;
			color1[2] = 255;
		}
		else if(col == START+4)
		{
			color1[0] = 0;
			color1[1] = 255;
			color1[2] = 255;
		}
		else if(col == START+5)
		{
			color1[0] = 255;
			color1[1] = 0;
			color1[2] = 255;
		}
		else if(col == START+6)
		{
			color1[0] = 125;
			color1[1] = 125;
			color1[2] = 125;
		}
		setColor(colors, x, col, BRIGHTNESS, color1);
	}
}

void spectrumAnalyzer(struct color colors[ROWS][COLS], int * spectrum){

	// start at highest frequency band
	int x = 6;

	// cycle through all led array columns
	for( int col = START; col < END; col++){

		// go though all of the frequency bands (6-0)
		if ( x >= 0){

			if(spectrum[x] > THRESH6){
				spectrumColor(colors, 6, col);
			}
			else if(spectrum[x] > THRESH5){
				spectrumColor(colors, 5, col);
			}
			else if(spectrum[x] > THRESH4){
				spectrumColor(colors, 4, col);
			}
			else if(spectrum[x] > THRESH3){
				spectrumColor(colors, 3, col);
			}
			else if(spectrum[x] > THRESH2){
				spectrumColor(colors, 2, col);
			}
			else if (spectrum[x] > THRESH1){
				spectrumColor(colors, 1, col);
			}
			else{
				spectrumColor(colors, 0, col);
			}
		}

		// move down a frequency band
		x--;
	}
}





