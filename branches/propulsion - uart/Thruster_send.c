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
   unsigned int channel;                                 /* variable for voltage in loop */
   unsigned int data;                                    /* variable sent to other pic */
   setup_adc(ADC_CLOCK_INTERNAL);                        /*  Setup ADC input*/
   setup_adc_ports(ALL_ANALOG);

   for(;;)                                               /* infinet loop */
   {
      data=0;                                            /* reset the work variable */
      for(channel = 0; channel <=2; channel++)
      {          /* loop through the input channels */
         set_adc_channel(channel);                       /* setup channel based on loop */
         vin[channel] = read_adc();                      /* read the input of the channel */
         delay_us(10);                                   /* small delay to give the pic time to read the input value */
         putc(channel);
         putc(vin[channel]);
      }
   }
}
