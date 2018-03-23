#include "ledFunctions.h"

void setWhite (struct color* colors, int quantity, int percent)
{
	for(int i = 0; i < quantity; i++)
	{
		colors[i].green = 255*percent/100;
		colors[i].red = 255*percent/100;
		colors[i].blue = 255*percent/100;
	}
	return;
}

void setBlack (struct color* colors, int quantity, int percent)
{
	for(int i = 0; i < quantity; i++)
	{
		colors[i].green = 0;
		colors[i].red = 0;
		colors[i].blue = 0;
	}
	return;
}
