/*
 * globalVariables.h
 *
 *  Created on: Apr 3, 2018
 *      Author: mann53
 */

#ifndef GLOBALVARIABLES_H_
#define GLOBALVARIABLES_H_

/*INCLUDES */
#include "ledFunctions.h"

/* used to keep track of millesonds for delay function */
 extern volatile int ms;

 /* Flag for knowing when user button 1 has been pressed */
 extern volatile int userBtnFlag;

 /* variable to keep track of user button current value */
 extern volatile int userBtnCurrent;

 /* variable to keep track of user button previous value */
 extern volatile int userBtnPrevious;

 /* Tells timer3 interrupt when to update ms variable */
 extern volatile int msCountFlag;

#endif /* GLOBALVARIABLES_H_ */
