/*
 * globalVariables.h
 *
 *  Created on: Apr 3, 2018
 *      Author: mann53
 */

#ifndef GLOBALVARIABLES_H_
#define GLOBALVARIABLES_H_

/* used to keep track of millesonds for delay function */
 extern volatile int ms;

 /* Flag for knowing when user button 1 has been pressed */
 extern volatile int userBtnFlag;
 extern volatile int userBtnCurrent;
 extern volatile int userBtnPrevious;

#endif /* GLOBALVARIABLES_H_ */
