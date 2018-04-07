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

void tim1_IT(void){

	// increment millsecond counter by 2
	ms = ms + 2;
}

void userB1_IT(void){

	// interrupt has fired so set user button 1 flag
	userBtnFlag = 1;
}
