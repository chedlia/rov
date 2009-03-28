//This will eventually control all 8 servos
#include "16F877A.h"                                  //identify pic
#device ADC=8    
#use delay(clock=8000000)                                      //8 bit analog capturevoid main()
unsigned int read;
int step;
int channel;
int oldpot[8];

void setspeed (void);
void main()
{
	setup_adc(adc_clock_internal);
	setup_adc_ports(ALL_ANALOG); 
	for(;;)
	{
		for(channel = 0; channel <=8; channel++)
		{
			
			set_adc_channel(0);
			delay_us(10);
			read=read_adc();
			if (read!=oldpot[channel])
				setspeed();
		}
	}
}
void setspeed(void)
{
	read=read/4;
	output_high(PIN_B0);
	delay_us(105);      
	for(step=0;step<30;++step)
	{
		if (step>read)
            output_low(PIN_B0);//  NEED HELP HERE!!!        
	}
	oldpot[channel]=read;
      delay_ms(.5);
}