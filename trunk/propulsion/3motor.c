/*   3 Motor PWM Control with 16F877A
*********************************************/

#include "16F877A.h"                                  //identify pic
#device ADC=8                                         //8 bit analog capture

#use delay(clock=8000000)                             //chip set at 8Mhz


void main()
{
   unsigned int vin1;                                 //  Vin1,2,3 are the variables
   unsigned int vin2;                                 //  that the potentiometer values 
   unsigned int vin3;                                 //  (one for each motor)are assigned
   unsigned int reverse1;                             //  too.
   unsigned int forward1;
   unsigned int reverse2;                             //  The three pair of forward and reverse
   unsigned int forward2;                             //  variables are used to control each
   unsigned int reverse3;                             //  motor independently
   unsigned int forward3;
   int step;                                          //  The step variable is used to count
                                                      //  through the for loop.  This and the 
                                                      //  delays will need to be tweeked to
                                                      //  enable correct duty cycle.
                                     
   setup_adc(ADC_CLOCK_INTERNAL);                     //  Setup ADC input
   setup_adc_ports(ALL_ANALOG);

   
   for(;;)                                           //  infinete loop
   {  
      set_adc_channel(0);                             //  start ADC capture on pin AN0
      vin1 = read_adc();
      delay_ms(10);                                   //  wait to allow chip time to read value
      
      set_adc_channel(1);                             //  start ADC capture on pin AN1
      vin2 = read_adc();
      delay_ms(10);                                   //  wait to allow chip time to read value
      
      set_adc_channel(2);                             //  start ADC capture on pin AN2
      vin3 = read_adc();
      delay_ms(10);                                   //  wait to allow chip time to read value
      
      reverse1=0;                                     //  Zero Variables
      forward1=0;
      If (vin1 < 120) reverse1=vin1;                  //  Seperate forward and reverse positions
      else reverse1=255;                              //  of pot and assign them to the proper
      If (vin1 > 130) forward1=vin1;                  //  variable from AN0
      else forward1=0;
      
      reverse2=0;                                     //  Zero Variables
      forward2=0;
      If (vin2 < 120) reverse2=vin2;                  //  Seperate forward and reverse positions
      else reverse2=255;                              //  of pot and assign them to the proper
      If (vin2 > 130) forward2=vin2;                  //  variable from AN1
      else forward2=0;
      
      reverse3=0;                                     //  Zero Variables
      forward3=0;
      If (vin3 < 120) reverse3=vin3;                  //  Seperate forward and reverse positions
      else reverse3=255;                              //  of pot and assign them to the proper
      If (vin3 > 130) forward3=vin3;                  //  variable from AN2
      else forward3=0;
      
      for(step=0;step<254;step++)                     //  For loop where on states occur
         {
            if (reverse1<step) output_high(PIN_B0);   //pin b0 on to motor one (reverse)
            else output_low(PIN_B0);                  //pin B0 off 
            
            if (forward1>step) output_high (pin_b1);  //pin B1 to motor one (forward)
            else output_low(pin_b1);                  //pin B1 off
            
            if (reverse2<step) output_high(PIN_B2);   //pin B2 to motor two (reverse)
            else output_low(PIN_B2);                  //pin B2 off
            
            if (forward2>step) output_high (pin_b3);  //pin B3 to motor two (forward)
            else output_low(pin_b3);                  //pin B3 off
            
            if (reverse3<step) output_high(PIN_B4);   //pin B4 on to motor three (reverse)
            else output_low(PIN_B4);                  //pin B4 off  
            
            if (forward3>step) output_high (pin_b5);  //pin B5 on to motor three (forward)
            else output_low(pin_b5);                  //pin B5 off
            
            delay_us(200);                            //Critical delay to help set duty
                                                      //cycle...needs testing
         }
   }
}
