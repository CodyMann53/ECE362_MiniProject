/*
 * interrupts.h
 *
 *  Created on: Apr 7, 2018
 *      Author: Cody Mann
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

/* Timer 1 is interrupt is used to increment a ms variable used for a ms delay function */
void tim1_IT(void);

/* Hitting user button 1 triggers this interrupt */
void userB1_IT(void);

#endif /* INTERRUPTS_H_ */
