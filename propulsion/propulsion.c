/*
 propulsion.c
 intended to control the propulsion system of the ROV.
 */

/* 
 NOTES: 
 Please place any general notes here. What is a general note? A note that may be needed to further explain why you chose to do something
 and to keep the rest of the code organized and concise. you may also offer ideas.
 Please place your name and time stamp by any contributed note.
 */	

#include "../header/ROV.h"

/*
 THRUST
 controls the propulsion motors thrust
 
 @param motor; 1,2,3, etc
 @param direction; FORWARD, REVERSE
 @param pwm; puls-width modulation
 */
void thrust(int motor, int direction, int pwm) {
	if (motorfeedback(motor)) {
	/*execute	 */	
	}
}
