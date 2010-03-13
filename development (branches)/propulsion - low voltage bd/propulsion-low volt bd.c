/*  propulsion.c
	3 Motor PWM Control with PIC 16F877A   
	and L298HN Bridge Driver
*********************************************/

#include "16F877A.h"                                  /* identify pic */
#device ADC=8                                         /* 8 bit analog capture*/
#fuses XT, PUT, NOWDT, NOPROTECT, BROWNOUT, NOCPD
#use delay(clock=4000000)                             /* chip set at 8Mhz*/


void main()
{
/*  Vin[0,1,2] are the variables that the potentiometer values (one for each motor)are assigned too*/
   unsigned int vin[3];
   unsigned int reverse1;
   unsigned int forward1;
   unsigned int reverse2;                             /*  The three pair of forward and reverse*/
   unsigned int forward2;                             /*  variables are used to control each */
   unsigned int reverse3;                             /*  motor independently*/
   unsigned int forward3;
   unsigned int channel = 0;
   int step;                                          /*  The step variable is used to count*/
                                                      /*  through the for loop.  This and the */
                                                      /*  delays will need to be tweeked to*/
                                                      /*  enable correct duty cycle.*/
                                     
   setup_adc(ADC_CLOCK_INTERNAL);                     /*  Setup ADC input*/
   setup_adc_ports(ALL_ANALOG);

   
   while(1)                                           /*  infinete loop*/
   {
      for(channel = 0; channel <=2; channel++){
         set_adc_channel(channel);
         vin[channel] = read_adc();
         delay_us(10);
         
      }


      If (vin[0] < 120) 
         reverse1=vin[0];                  /*  Seperate forward and reverse positions*/
      else 
         reverse1=255;                              /*  of pot and assign them to the proper*/
      If (vin[0] > 130) 
         forward1=vin[0];                  /*  variable from AN0*/
      else 
         forward1=0;
      
      If (vin[1] < 120) 
         reverse2=vin[1];                  /*  Seperate forward and reverse positions*/
      else 
         reverse2=255;                              /*  of pot and assign them to the proper*/
      If (vin[1] > 130) 
         forward2=vin[1];                  /*  variable from AN1*/
      else 
         forward2=0;
      
      If (vin[2] < 120) 
         reverse3=vin[2];                  /*  Seperate forward and reverse positions*/
      else 
         reverse3=255;                              /*  of pot and assign them to the proper*/
      If (vin[2] > 130) 
         forward3=vin[2];                  /*  variable from AN2*/
      else 
         forward3=0;
      
      for(step=0;step<254;step++)                     /*  For loop where on states occur*/
         {
            if (reverse1<step) output_high(PIN_B0);   /*pin b0 on to motor one (reverse)*/
            else output_low(PIN_B0);                  /*pin B0 off*/
            
            if (forward1>step) output_high (pin_b1);  /*pin B1 to motor one (forward)*/
            else output_low(pin_b1);                  /*pin B1 off*/
            
            if (reverse2<step) output_high(PIN_B2);   /*pin B2 to motor two (reverse)*/
            else output_low(PIN_B2);                  /*pin B2 off*/
            
            if (forward2>step) output_high (pin_b3);  /*pin B3 to motor two (forward)*/
            else output_low(pin_b3);                  /*pin B3 off*/
            
            if (reverse3<step) output_high(PIN_B4);   /*pin B4 on to motor three (reverse)*/
            else output_low(PIN_B4);                  /*pin B4 off*/
            
            if (forward3>step) output_high (pin_b5);  /*pin B5 on to motor three (forward)*/
            else output_low(pin_b5);                  /*pin B5 off*/
            
            delay_us(200);                            /*Critical delay to help set duty*/
                                                      /*cycle...needs testing*/
         }
   }
}
