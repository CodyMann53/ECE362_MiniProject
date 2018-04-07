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

void tim2_IT(void){

	// increment millsecond counter by 2
	ms = ms + 2;
}


void tim3_IT(void){

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
