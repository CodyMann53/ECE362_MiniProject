/*
 * ledFunctions.h
 *
 *  Created on: Apr 7, 2018
 *      Author: Cody Mann
 */

#ifndef LEDFUNCTIONS_H_
#define LEDFUNCTIONS_H_

/* MACRO DEFINITIONS */
struct color{
	char green;
	char red;
	char blue;
}color;

/* FUNCTION DECLARATIONS */

/* Updates the LED strip. Data parameter is an array of colors
and numBytes is the number of bytes that needs to be written to the LED strip with 3 bytes per LED. */
void ledStripWrite(struct color* data, int numBytes);

/* sets a certain position in the colors array to white with percent brightness. */
void setWhite (struct color* colors, int position, int percent);

/* sets a certain position in the colors array to off.*/
void setBlack (struct color* colors, int position);

/* sets a certain position in the colors array to blue with percent brightness. */
void setBlue (struct color* colors, int position, int percent);

/* sets a certain position in the colors array to red with percent brightness. */
void setRed (struct color* colors, int position, int percent);

/* sets a certain position in the colors array to green with percent brightness. */
void setGreen (struct color* colors, int position, int percent);

#endif /* LEDFUNCTIONS_H_ */
