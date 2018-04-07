/*
 * interrupts.h
 *
 *  Created on: Apr 7, 2018
 *      Author: Cody Mann
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

/* Timer 1 is interrupt is used to increment a ms variable used for a ms delay function */
void tim2_IT(void);

/* used for debouncing user push button 1 */
void tim3_IT(void);

#endif /* INTERRUPTS_H_ */
