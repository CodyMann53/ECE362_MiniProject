/*
 * filter.h
 *
 *  Created on: Apr 9, 2018
 *      Author: Cody Mann
 */

#ifndef FILTER_H_
#define FILTER_H_

/* updates the spectrum array by reading all the band filter values from the IC filtering chip */
void filter(int * spectrum);

/* sets the reset (PA3) pin on the filtering IC chip high(1) or low(0) */
void reset(int value);

/* sets the strobe (PA2) pin on the filtering IC chip high(1) or low(0) */
void strobe(int value);

#endif /* FILTER_H_ */
