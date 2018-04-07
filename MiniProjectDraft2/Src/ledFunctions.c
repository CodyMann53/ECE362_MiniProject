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


