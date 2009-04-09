/*   3 Motor PWM Control with 16F877A
*********************************************/

/*
So I've reworked the first part of the code. Breaking the logic up by motor seems like a good
way to do things, so that's what I did. I don't have the software setup to test this code, so
Matt you'll have to test it and see how it works. The sooner you can show up on Friday the better
I'd like to get my computer set up with the software needed.
*/


#include "16F877A.h"		/*identify pic*/
#define MINFORWARD 130			/*This is the lowest the value can be, and still be in FORWARD motion*/
#define MAXREVERSE 120			/*This is the highest the value can be, and still be in REVERSE motion*/

#device ADC=8		/*8 bit analog capture*/

#use delay(clock=8000000)		/*chip set at 8Mhz*/

/*We'll be breaking our logic up into seperate motors.*/
struct Motor
{
	int forwardValue;
	int reverseValue;
	int potValue;
	int ADCNum;
	int direction;
};
void readPot(Motor motor)
{
	set_adc_channel(motor.ADCNum);		/* start ADC capture on pin*/
	motor->potValue = read_adc();
}

void setDirection(Motor motor)
{
	if (motor.potValue < MAXREVERSE)
	{
		motor.reverseValue = motor.potValue;
		motor.forwardValue = 0;
		motor.direction = REVERSE;
	}
	else if (motor.potValue > MINFORWARD)
	{
		motor.reverseValue = 0;
		motor.forwardValue = motor.potValue;
		motor.direction = FORWARD;
	}
	else
	{
		motor.reverseValue = 0;
		motor.forwardValue = 0;
		motor.direction = STOP;
	}
}



void main()
{															
	motor one;  	/*These motors need to be named better, by location?*/
	motor two;
	motor three;
	int step;										/* The step variable is used to count
														 through the for loop.  This and the 
														 delays will need to be tweeked to
														 enable correct duty cycle.*/

	setup_adc(ADC_CLOCK_INTERNAL);						/*  Setup ADC input*/
	setup_adc_ports(ALL_ANALOG);
   while(1)												/*  loop forever*/
   {
		readPot(one;)
		setDirection(one);
		/* we may need the pauses in here again, but we'll see*/
		readPot(two);
		setDirection(two);

		readPot(three);
		setDirection(three);

		/*I'm not really sure what we're doing with this for-loop, so for now it's just modified
		to work with the code changes I made, however I believe it can be optimized a great deal
		
		Currently this for loop (not counting execution time for any of the functions) takes
		about 50 seconds to run!!! Because of the "Critical Delay" at the end. That means we could
		only update our speed/direction once a minute!		
		*/

		for(step=0;step<254;step++)                     /*   For loop where on states occur*/
		 {
			if (one.reverseValue<step) output_high(PIN_B0);   /* pin b0 on to motor one (reverse)*/
			else output_low(PIN_B0);                  /* pin B0 off */
		    
			if (one.forwardVale>step) output_high (pin_b1);  /*pin B1 to motor one (forward)*/
			else output_low(pin_b1);                 /* pin B1 off*/
		    
			if (two.reverseValue<step) output_high(PIN_B2);   /* pin B2 to motor two (reverse)*/
			else output_low(PIN_B2);                  /* pin B2 off*/
		    
			if (two.forwardValue>step) output_high (pin_b3);  /* pin B3 to motor two (forward)*/
			else output_low(pin_b3);                  /* pin B3 off*/
		    
			if (three.reverseValue<step) output_high(PIN_B4);   /* pin B4 on to motor three (reverse)*/
			else output_low(PIN_B4);                  /* pin B4 off  */
		    
			if (three.forwardValue>step) output_high (pin_b5);  /* pin B5 on to motor three (forward)*/
			else output_low(pin_b5);                  /* pin B5 off*/
		    
			delay_us(200);                            /* Critical delay to help set duty cycle...needs testing*/
		 }
   }
}
