/*   3 Motor PWM Control with 16F877A
*********************************************/

/*
I've look at this code a little more and made additional changes. I think the problem has been narrowed
down to the functions.
For example when we step into readPot everything works fine until we step out. After that the data is lost.
I tried using pointers but was unable to solve this problem (I'm not really good with pointers yet)
If we can find a way to pass the motor struct by reference we may be able to solve this problem.
*/


#include "16F877A.h"      /*identify pic*/
#define MINFORWARD 130         /*This is the lowest the value can be, and still be in FORWARD motion*/
#define MAXREVERSE 120         /*This is the highest the value can be, and still be in REVERSE motion*/
//#define REVERSE 255
//#define FORWARD 0
//#define STOP 125

#device ADC=8      /*8 bit analog capture*/

#use delay(clock=8000000)      /*chip set at 8Mhz*/

/*We'll be breaking our logic up into seperate motors.*/
typedef struct Motor                  /* we need to make a type definition in order to use "Motor motor"*/
{
   int forwardValue;
   int reverseValue;
   int potValue;
   int ADCNum;
  // int direction; //we don't use this
} Motor;                              /*typedef name*/

void readPot(Motor motor)
{
   set_adc_channel(motor.ADCNum);      /* start ADC capture on pin*/
   motor.potValue = read_adc();         /*changed from -> to .*/
  // delay_ms(10);
}

void setDirection(Motor motor)
{
   if (motor.potValue < MAXREVERSE)
   {
      motor.reverseValue = motor.potValue; // I don't think the motor.potValue
      motor.forwardValue = 0;
     // motor.direction = REVERSE;
   }
   else if (motor.potValue > MINFORWARD)
   {
      motor.reverseValue = 0;
      motor.forwardValue = motor.potValue;
     // motor.direction = FORWARD;
   }
   else
   {
      motor.reverseValue = 0;
      motor.forwardValue = 0;
     // motor.direction = STOP;
   }
}



void main()
{
   motor one;     /*These motors need to be named better, by location?*/
   motor two;
   motor three;
   int step;                              /* The step variable is used to count
                                           through the for loop.  This and the
                                           delays will need to be tweeked to
                                           enable correct duty cycle.*/

   setup_adc(ADC_CLOCK_INTERNAL);                  /*  Setup ADC input*/
   setup_adc_ports(ALL_ANALOG);

   /*Declare which pins to use for each motor*/
   one.ADCNum = 0;			/*pin AN0*/
   two.ADCNum = 1;			/*pin AN1*/
   three.ADCNum = 2;		/*pin AN2*/

   while(1)                                    /*  loop forever*/
   {
      readPot(one);
      setDirection(one);
      /* we may need the pauses in here again, but we'll see*/

      readPot(two);
      setDirection(two);

      readPot(three);
      setDirection(three);


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
		    
			delay_us(200);                            /*MicroSeconds Critical delay to help set duty cycle...needs testing*/
		 }
   }
}
