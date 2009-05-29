/*   propulsion.c
LBCC-ROV 2009
Programed by Matt Seidlitz
    3 Thruster PWM Control with 16F877A   
*********************************************/

#include "16F877A.h"                                     /* identify pic */
#device ADC=8                                            /* 8 bit analog capture*/
#fuses XT, PUT, NOWDT, NOPROTECT, BROWNOUT, NOCPD        /* enable nominal speed external clock, enable power up timer
                                                         /* disable watchdog timer, program memory protect disabled,
                                                         /* brownout detect/reset enabled, EEPROM data memory protect disabled */
#use delay(clock=4000000)                                /* chip set at 4Mhz*/
#include "math.h" 
#use rs232 (baud=9600,uart1)
void main()
{

   unsigned int vin[3];                                  /* vin [0,1,2] varibles the potentiometer values are stored into */
   unsigned int channel;                               /* variable for voltage in loop */
   unsigned int speed[3];                                /* variable to set the speed of motor 1,2,3 */ 
   unsigned int work;                                    /* binary output on bank B variable */
   int step;                                             /* The step variable is used to count through the duty cycle */
   unsigned int16 data;
   
   setup_adc(ADC_CLOCK_INTERNAL);                        /*  Setup ADC input*/
   setup_adc_ports(ALL_ANALOG);

   for(;;)                                               /* infinet loop */
   {
      work=0;                                            /* reset the work variable */
      for(channel = 0; channel <=2; channel++){          /* loop through the input channels */
         data=getc();
         if (data < 1000)
            vin[0]=data;
         if (data < 2000 && data >999)
            vin[1]=data-1000;
         else 
            vin[2]=data-2000;
         
         If (vin[channel] < 120)                         /* reverse position*/
            speed[channel]=vin[channel]*-.5+80;          /* calculate the time on based on the input.  returns a value from 80-20 */
         else If (vin[channel] > 135){                   /* forward position*/
            work+=4^(channel-1);                         /* add binary of port 1,3, or 5 to indicate forward to motor controller */
            speed[channel]=(vin[channel]-135)*.5+20; }   /* calculate the time on based on the input. returns a value from 20-80 */              
         else speed[channel]=0;                          /* potentiometer input is neutral motor is off */         
   }
      work+=42;                                          /*  all motor pins on*/

      for(step=0;step<100;step++)                        /*  For loop where on states occur*/
         {
            if (speed[0]==step) 
               work-=2;                                  /* pin B0 off */
            if (speed[1]==step) 
               work-=8;                                  /* pin B3 off*/
            if (speed[2]==step) 
               work-=32;                                 /* pin B5 off*/
         
            output_B(work);                              /* turn on outputs on bank B based on binary */
            delay_us (2); 
         }
   }
}
