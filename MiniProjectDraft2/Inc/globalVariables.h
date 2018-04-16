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

 /* variable to keep track of user button current value */
 extern volatile int userBtnCurrent;

 /* variable to keep track of user button previous value */
 extern volatile int userBtnPrevious;

 /* Tells timer3 interrupt when to update ms variable */
 extern volatile int msCountFlag;

 extern int red[3];
 extern int green[3];
 extern int blue[3];
 extern int magenta[3];
 extern int yellow[3];
 extern int teal[3];
 extern int off[3];

#endif /* GLOBALVARIABLES_H_ */
