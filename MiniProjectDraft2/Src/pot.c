/*
 * pot.c
 *
 *  Created on: Apr 24, 2018
 *      Author: Cody Mann
 */
#include "pot.h"
#include "adc.h"
#include "globalVariables.h"
void readBrightness(void){

	//start ADC conversion
	HAL_ADC_Start(&hadc);

	//wait for ADC conversion
	HAL_ADC_PollForConversion(&hadc,0);

	//retrieve  converted value
	HAL_ADC_GetValue(&hadc);

	// wait for conversion to be completed
	HAL_ADC_PollForConversion(&hadc,0);

    brightness = ( HAL_ADC_GetValue(&hadc) ) / 273;

    // stop ADC conversion
    HAL_ADC_Stop(&hadc);




}
