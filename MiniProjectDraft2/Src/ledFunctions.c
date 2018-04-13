/*
 * ledFunctions.c
 *
 *  Created on: Apr 7, 2018
 *      Author: Andrew Osborne
 */

/* INCLUDES */
#include "ledFunctions.h"

/* FUNCTION DEFINITIONS */

void setWhite (struct color* colors, int position, int percent)
{
		colors[position].green = 255*percent/100;
		colors[position].red = 255*percent/100;
		colors[position].blue = 255*percent/100;

	return;
}

void setBlack (struct color* colors, int position)
{
		colors[position].green = 0;
		colors[position].red = 0;
		colors[position].blue = 0;

	return;
}

void setBlue (struct color* colors, int position, int percent)
{
		colors[position].green = 0;
		colors[position].red = 0;
		colors[position].blue = 255*percent/100;

	return;
}

void setRed (struct color* colors, int position, int percent)
{
		colors[position].green = 0;
		colors[position].red = 255*percent/100;
		colors[position].blue = 0;

	return;
}

void setGreen (struct color* colors, int position, int percent)
{
		colors[position].green = 255*percent/100;
		colors[position].red = 0;
		colors[position].blue = 0;

	return;
}

void allGreen (struct color * colors, int percent){

	for (int x = 0; x < LEDS; x++){
		setGreen(colors, x, percent);
	}
}

void allRed (struct color * colors, int percent){

	for (int x = 0; x < LEDS; x++){
		setRed(colors, x, percent);
	}
}

void allWhite(struct color * colors, int percent){

	for (int x = 0; x < LEDS; x++){
		setWhite(colors, x, percent);
	}
}

void setManual (struct color * colors, char colorRed, char colorGreen, char colorBlue, int position, int percent){

	colors[position].green = colorGreen * percent/ 100;
	colors[position].red = colorRed * percent / 100 ;
	colors[position].blue = colorBlue * percent / 100;


}

void allManualColor(struct color * colors, char colorRed, char colorGreen, char colorBlue, int percent){

	for (int x = 0; x < LEDS; x++){
		setManual(colors, colorRed, colorGreen, colorBlue, x, percent);
	}
}

void modeOne(struct color * colors, int * spectrum){

	if ( spectrum[0] > 100){

		if (spectrum[4] > 100){
			allRed(colors, 100);
		}
		else if ( spectrum[5] > 100){
			allGreen(colors, 100);
		}
		else{
			allWhite(colors, 100);
		}
	}
	else{
		allRed(colors, 0);
	}

}




