/*
 * filter.c
 *
 *  Created on: Apr 9, 2018
 *      Author: Cody Mann
 */
#include "stm32f0xx_hal.h"
#include "gpio.h"
#include "tim.h"
#include "interrupts.h"
#include "filter.h"
#include "adc.h"

void filter(int * spectrum){


	//set reset high
	reset(1);

	// dealy 1 us
	delay_us(1);

	//set reset low
	reset(0);

	// loop through all of the bands and read their dc values
	for (int i = 0; i < 7; i++){

		// strobe high
		strobe(1);

		// delay 18 us
		delay_us(18);

		// strobe low
		strobe(0);

		// wait 36 us for output to settle
		delay_us(36);

		//start ADC conversion
		HAL_ADC_Start(&hadc);

		//wait for ADC conversion
		HAL_ADC_PollForConversion(&hadc,0);

		//retrieve  converted value
		spectrum[i] = HAL_ADC_GetValue(&hadc);

	    // stop ADC conversion
	    HAL_ADC_Stop(&hadc);

	    // wait for 18 us to satisfy strobe to strobe timing requirements
	    delay_us(18);

	}
}

void reset(int value){

	if (value == 1){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	}

}

void strobe(int value){

	if (value == 1){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
	}
}
