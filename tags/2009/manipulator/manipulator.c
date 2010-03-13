/*  manipulator.c
    LBCC-ROV 2009, programed by Matt Seidlitz
               and Joel Lonbeck.
    7 stepper Motor Control with 16F877A   
*********************************************/
#include "16F877A.h"                                      /* identify pic */
#device ADC=8                                             /* 8 bit analog capture*/
#fuses XT, PUT, NOWDT, NOPROTECT, BROWNOUT, NOCPD         /* enable nominal speed external clock, enable power up timer
                                                          /* disable watchdog timer, program memory protect disabled,
                                                          /* brownout detect/reset enabled, EEPROM data memory protect disabled */
#use delay(clock=4000000)                                 /* chip set at 4Mhz*/
#include "math.h" 

unsigned int Pot_pos[7];                                   /* vin [0,1,2] varibles the potentiometer values are stored into */
unsigned int multi;
unsigned int channel;                                      /* variable for voltage in loop */
unsigned int16 Cur_Loc[7];                                 /* variable to set the speed of motor 1,2,3 */
unsigned int Status[7];
unsigned int movement;                                     /* binary output on bank B variable */
unsigned int direction;
signed int16 Next_Loc[7];
int step;                                                  /* The step variable is used to count through the duty cycle */

void main()
{
   setup_adc(ADC_CLOCK_INTERNAL);                         /*  Setup ADC input*/
   setup_adc_ports(ALL_ANALOG);
   
   /* initialize Next_Loc */
   for(channel = 0; channel < 7; channel++) {
      set_adc_channel(channel);
      Cur_Loc[channel] = read_adc();                       
   }

   /* begin control*/
   while(true)                                            /* infinite loop */
   {
      direction = 0;
      movement = 127;
      
      /*initialize channels and read data*/
      for(channel = 0; channel < 7; channel++) {
         set_adc_channel(channel);
         delay_us(20);
         Pot_Pos[channel] = read_adc();                        /* read the input of the channel */
         delay_us(10);                                         /* small delay to give the pic time to read the input value */
         Next_Loc[channel] = Pot_Pos[channel] - Cur_Loc[channel]; /* calculate the next location*/
         status[channel] = 1;                                 /* status is 1 till visited*/
         
         if(Next_Loc[channel] < 0)
            direction += pow(2,channel);
      }

      /* Send pulses*/
      for(step = 0; step < 100; step++){                     /*  For loop where on states occur*/           
         for(channel = 0; channel < 7; channel++) {
            if(Pot_Pos[channel] == Cur_Loc[channel]){
               if(status[channel] == 1) {
                  movement -= pow(2,channel);
                  status[channel] = status[channel] - 1;  
               }
            }
            if (Pot_Pos[channel] > Cur_Loc[channel])
               Cur_Loc[channel] = Cur_Loc[channel] + 1;
            if (Pot_Pos[channel] < Cur_Loc[channel])
               Cur_loc[channel] = Cur_Loc[channel] - 1;
         }
         for(multi=0; multi <26; multi++) {
            output_B(direction);                            /* turn on outputs on Bank B based on binary */
            output_D(movement);                             /* turn on outputs on bank D based on binary */
            delay_us(250);                                  /* waits so a pulse can be felt by the stepper*/
            output_D(0);                                    /* turn off all pins on bank D*/
            output_B(0);
            
         }
      }
   }
}  
