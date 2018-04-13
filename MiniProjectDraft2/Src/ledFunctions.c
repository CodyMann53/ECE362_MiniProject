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
			allRed(colors, BRIGHTNESS);
		}
		else if ( spectrum[5] > 100){
			allGreen(colors, BRIGHTNESS);
		}
		else{
			allBlue(colors, BRIGHTNESS);
		}
	}
	else{
		allOff(colors);
	}
}

void SpectrumAnalyzer(struct color colors[ROWS][COLS]){






}





