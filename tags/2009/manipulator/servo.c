/*   arm.c
    LBCC-ROV 2009, programed by Matt Seidlitz
               and Joel Longneck.
    7 stepper Motor Control with 16F877A   
*********************************************/
#include "16F877A.h"                                      /* identify pic */
#device ADC=8                                             /* 8 bit analog capture*/
#fuses XT, PUT, NOWDT, NOPROTECT, BROWNOUT, NOCPD         /* enable nominal speed external clock, enable power up timer
                                                          /* disable watchdog timer, program memory protect disabled,
                                                          /* brownout detect/reset enabled, EEPROM data memory protect disabled */
#use delay(clock=4000000)                                 /* chip set at 4Mhz*/
#include "math.h" 

//unsigned int pot_servo;
unsigned int16 servo_pos;
unsigned int16 Pot_Pos;
long x;
void servo(void);

void main ()
{
   setup_adc(ADC_CLOCK_INTERNAL);                         /*  Setup ADC input*/
   setup_adc_ports(ALL_ANALOG);
   
   while(true)                                            /* infinite loop */
   {
      set_adc_channel(0);
      delay_us(20);
      Pot_Pos=read_adc();
      delay_us(20);
      
      servo();
    }
}

void servo(void)
{     x = 1250 + (4*Pot_pos);
      output_bit(PIN_B0,1);
      DELAY_US(x); 
      output_bit(PIN_B0,0);
      DELAY_US(20000-x);
      servo_pos=Pot_Pos;
} 
