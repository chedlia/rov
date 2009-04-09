/*
 sensors.c
 intended to control the sensors of the ROV.
 */

/* 
 NOTES: 
 Please place any general notes here. What is a general note? A note that may be needed to further explain why you chose to do something
 and to keep the rest of the code organized and concise. you may also offer ideas.
 Please place your name and time stamp by any contributed note.
 */	

#include "../ROV.h"

/*
 MOTORFEEDBACK
 returns true if everything's ok with the motor, and false if there is a problem.
 note: default return is false... just in case.
 @param motor; 1,2,3, etc
 @return boolean
 */
bool motorfeedback(int motor) {
	if("everything's ok")
	{
		return true;
	}
	return false;
}

/*
 DEPTHMETER
 retrieves the current reading from the depth meter and returns the calculated depth
 hydrostatic prssure at depth d is p = 1 atm + density*g*d
 gauge pressure is p - 1 atm so gauge prssure is given by p = density*g*d
 and d is found by d = p/(density*g);
 
 @param pressure; the reading from the pressure sensor (gauge pressure)
 @param gravity; the local gravity
 @param density; the density of the fluid the ROV is traveling through
 @return depth;
 */
float depthmeter(float pressure, float gravity, float density) {
	//physics pg451 calculating the depth.
	float depth = pressure / ( density * gravity);
	return depth;
}
