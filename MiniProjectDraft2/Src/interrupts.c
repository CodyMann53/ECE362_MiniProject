/*
 * interrupts.c
 *
 *  Created on: Apr 7, 2018
 *      Author: Cody Mann
 */
#include "globalVariables.h"
#include "main.h"
#include "interrupts.h"
#include "tim.h"

void tim3_IT(void){

	// update ms counter for delay if delay function sets the msCount flag
	if (msCountFlag == 1){
		msDelay = msDelay + 5;
	}

	// update ms counter
	ms = ms + 5;

	// set write flag every 20 ms
	if (ms >= 6){

		//reset ms
		ms = 0;

		writeFlag = 1;
	}

	msCount = msCount + 5;


	// update user button current value
	userBtnCurrent = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

	// check to see if there was a transition on the GPIOA PIN 0 input pin from low to high
	if ( (userBtnCurrent == 1) & (userBtnPrevious == 0) ){

		//set user button flag to signal that it has been pressed
		userBtnFlag = 1;
	}

	//update user button previous
	userBtnPrevious = userBtnCurrent;

}


