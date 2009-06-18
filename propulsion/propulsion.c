/*   propulsion.c
LBCC-ROV 2009
Programed by Matt Seidlitz
    3 Thruster PWM Control with 16F877A   
*********************************************/

#include "16F877A.h"                                     /* identify pic */
#device ADC=10                                           /* 8 bit analog capture*/
#fuses XT, PUT, NOWDT, NOPROTECT, BROWNOUT, NOCPD        /* enable nominal speed external clock, enable power up timer
                                                         /* disable watchdog timer, program memory protect disabled,
                                                         /* brownout detect/reset enabled, EEPROM data memory protect disabled */
#use delay(clock=4000000)                                /* chip set at 4Mhz*/
#include "math.h" 

void main()
{

   unsigned int16 vin[3];                                /* vin [0,1,2] varibles the potentiometer values are stored into */
   unsigned int channel;                                 /* variable for voltage in loop */
   unsigned int16 speed[3];                                /* variable to set the speed of motor 1,2,3 */ 
   unsigned int work;                                    /* binary output on bank B variable */
   int step;                                             /* The step variable is used to count through the duty cycle */
                                     
   setup_adc(ADC_CLOCK_INTERNAL);                        /* Setup ADC input*/
   setup_adc_ports(ALL_ANALOG);

   while(true)                                           /* infinite loop */
   {
      work=0;                                            /* reset the work variable */
      
      for(channel = 0; channel <=2; channel++){          /* loop through the input channels */
         set_adc_channel(channel);                       /* setup channel based on loop */
         vin[channel] = read_adc();                      /* read the input of the channel */
         delay_cycles(100);                                    /* small delay to give the pic time to read the input value */
         If (channel == 0){
            If (vin[channel] < 510)                         /* reverse position*/
               speed[channel]=vin[channel]*-0.6 + 325;          /* calculate the time on based on the input.  returns a value from 80-20 */
            else If (vin[channel] > 514){                   /* forward position*/
               work+=1;                         /* add binary of port 1,3, or 5 to indicate forward to motor controller */
               speed[channel]=vin[channel]*0.6-288;      /* calculate the time on based on the input. returns a value from 20-80 */                    
            }
            else speed[channel]=0;        
         }
         if (channel == 1) {
            If (vin[channel] < 510)                         /* reverse position*/
               speed[channel]=vin[channel]*-0.6 + 325;          /* calculate the time on based on the input.  returns a value from 80-20 */
            else If (vin[channel] > 514){                   /* forward position*/
               work+=4;                         /* add binary of port 1,3, or 5 to indicate forward to motor controller */
               speed[channel]=vin[channel]*0.6 - 288;      /* calculate the time on based on the input. returns a value from 20-80 */                         
            
            }
            else speed[channel]=0;        
         }
         /* vertical thrust */
         If (channel == 2){
            If (vin[channel] < 465)                         /* reverse position*/
               speed[channel]=vin[channel]*-0.126 + 80;          /* calculate the time on based on the input.  returns a value from 80-20 */
            else If (vin[channel] > 565){                   /* forward position*/
               work+=16;                         /* add binary of port 1,3, or 5 to indicate forward to motor controller */
               speed[channel]=vin[channel]*0.126 - 50;      /* calculate the time on based on the input. returns a value from 20-80 */ 
            }
            else speed[channel]=0;        
         }
         /* horizontal thrust */
               }
      
      work+=42;                                          /*  all motor pins on*/

      for(step=0;step<87;step++) {                       /*  For loop where on states occur*/
         if (speed[0]==step) 
            work-=2;                                  /* pin B0 off */
         if (speed[1]==step) 
            work-=8;                                  /* pin B3 off*/
         if (speed[2]==step) 
            work-=32;                                 /* pin B5 off*/
      
         output_B(work);                              /* turn on outputs on bank B based on binary */
         delay_cycles( 8 );                                 /* delay for pwm */
      }
   }
}
