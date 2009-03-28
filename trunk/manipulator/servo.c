//Yes I know there are no comments!!!  It is almost 3:00am
//for crying out loud!!!

#include "16F877A.h"                                 //identify pic
#device ADC=10    
#use delay(clock=8000000)                                      //8 bit analog capturevoid main()
#include <math.h> 
   int16 read;
   int channel;
   int oldpot[8];
   int out;
void setspeed (void);
void main()
{
   setup_adc(adc_clock_internal);
   setup_adc_ports(ALL_ANALOG); 
   for(;;)
   {
      for(channel = 0; channel <=8; channel++)
      {         
         set_adc_channel(channel);
         delay_us(10);
         read=read_adc();
         if (read!=oldpot[channel])
            setspeed();
      }
   }
}
void setspeed(void)
{
      out=pow(2,(channel));
      output_B(out);
      delay_us(989);      
      delay_us(read);
      output_B(0);
      oldpot[channel]=read;
      delay_ms(18);
}
