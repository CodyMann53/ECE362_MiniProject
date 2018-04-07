/*
 * interrupts.c
 *
 *  Created on: Apr 7, 2018
 *      Author: Cody Mann
 */
#include "globalVariables.h"
#include "main.h"
#include "interrupts.h"

/* Timer 1 is interrupt is used to increment a ms variable used for a ms delay function */
void tim1_IT(void){

	// increment millsecond counter by 2
	ms = ms + 2;
}

void tim2_IT(void){

}
