/*
This program controls 8 servos with a pic and 8 potentiometers
*/

#include "16F877A.h"			//identify pic
#device ADC=10
#use delay(clock=8000000)       //8 bit analog capturevoid main()
#include <math.h>
   int16 read;
   int channel;
   int oldpot[8];
   int out;

//initialize functions
void setspeed (void);

// main
void main()
{
   setup_adc(adc_clock_internal);      // setup the internal clock
   setup_adc_ports(ALL_ANALOG);        // tell pic we want bank A to be analog
   for(;;)
   {
      for(channel = 0; channel <=8; channel++)   // loop through all our chanels and check for changes
      {
         set_adc_channel(channel);     // set which chanel to read from
         delay_us(20);                 // give it some time to think. note: we get warnings if shorter delay
         read=read_adc();              // reads input to the chip
         if (read!=oldpot[channel])    // set the speed if we detect a change
            setspeed();
      }
   }
}

// Set the speed and angle of servo
void setspeed(void)
{
      oldpot[channel]=read;      // keep track of the current chanels position
      read=read + 989;           // delay 1 ms
      out=pow(2,(channel));      // convert chanel to binary
      output_B(out);             // turn on
      delay_us(read);            // give a pulse to set the angle
      output_B(0);               // turn off all chanels
     // delay_ms(18);
}
