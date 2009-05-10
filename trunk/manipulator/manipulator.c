/*   manipulator.c
    8 stepper Motor Control with 16F877A   
*********************************************/

#include "16F877A.h"                                      /* identify pic */
#device ADC=8                                             /* 8 bit analog capture*/
#fuses XT, PUT, NOWDT, NOPROTECT, BROWNOUT, NOCPD         /* enable nominal speed external clock, enable power up timer
                                                          /* disable watchdog timer, program memory protect disabled,
                                                          /* brownout detect/reset enabled, EEPROM data memory protect disabled */
#use delay(clock=4000000)                                 /* chip set at 4Mhz*/
#include "math.h" 

void main()
{

   unsigned int vin[8];                                   /* vin [0,1,2] varibles the potentiometer values are stored into */
   unsigned int channel;                                  /* variable for voltage in loop */
   unsigned int location[8];                              /* variable to set the speed of motor 1,2,3 */
   unsigned int work;                                     /* binary output on bank B variable */
   unsigned int direction;
   unsigned int position[8];
   int step;                                              /* The step variable is used to count through the duty cycle */
                                     
   setup_adc(ADC_CLOCK_INTERNAL);                         /*  Setup ADC input*/
   setup_adc_ports(ALL_ANALOG);

   while(true)                                            /* infinite loop */
   {
      direction = 0;
      work = 0;                                           /* reset the work variable */
      for(channel = 0; channel <= 7; channel++){          /* loop through the input channels */
         set_adc_channel(channel);                        /* setup channel based on loop */
         vin[channel] = read_adc();                       /* read the input of the channel */
         delay_us(10);                                    /* small delay to give the pic time to read the input value */
         //vin[channel]*multiplyer to set position?
         
         if (vin[channel] == position[channel])           /* if the position is equal the the input then stay there*/
            location[channel] = vin[channel];
            
         else if (vin[channel] > position[channel])       /* if the input is greater than the position then move forwards to that position*/
            location[channel] = vin[channel] - position[channel];
    
         else if (vin[channel] < position[channel])  {    /* if the input is less than the position then turn on reverse and go to that position*/
            location[channel] = position[channel] - vin[channel];
            direction += pow(2,channel);
         }
      }
      for(step = 0; step < 100; step++)                    /*  For loop where on states occur*/
         {
            for(channel = 0; channel <= 7; channel++){     /* loop through the channels*/
            
               if (position[channel] == location[channel]) /* if the position is in the correct location turn of that pin */
                 work -= pow(2,channel);                    
                 
               else if (position[channel] > location[channel])/* if the position is beyond the location go down one step*/
                  position[channel] += 1;
                  
               else if (position[channel]<location[channel])/* if the position is before the location move one step*/
                  position[channel] -= 1;
            }
            output_B(direction);                            /* turn on outputs on Bank B based on binary */
            output_D(work);                                 /* turn on outputs on bank D based on binary */
            delay_ms (20);                                  /* waits so a pulse can be felt by the stepper*/
            output_D(0);                                    /* turn off all pins on bank D*/
            delay_ms (2);                                   /* needs tweeking should equal previous delay with time spent on statements above*/
         }
   }
}
