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

/* variable delcarations */
unsigned int vin[8];                                      /* vin [0,1,2] varibles the potentiometer values are stored into */
unsigned int channel;                                     /* variable for voltage in loop */
unsigned int location[7];                                 /* variable to set the speed of motor 1,2,3 */
unsigned int movement;                                    /* binary output on bank B variable */
unsigned int direction;
unsigned int position[7];
int step;                                                 /* The step variable is used to count through the duty cycle */
unsigned int servo_pos=0;
unsigned int bin[7];                           			  /* array used to determin active motors*/

/*function declarations */
void servo (void);
void dec_bin(unsigned int number);
      
/* main 
*/
void main()
{
	setup_adc(ADC_CLOCK_INTERNAL);                         /*  Setup ADC input*/
	setup_adc_ports(ALL_ANALOG);

	/* infinite loop */
	while(true)                                            
	{
		direction = 0;                              		/* resent direction */
		movement = 127;                                     /* reset  movement */

		for (channel =0;channel<8;channel++) {
			set_adc_channel(channel);                       /* setup channel based on loop */
			delay_us(20);
			vin[channel] = read_adc();                      /* read the input of the channel */
			delay_us(10);                                   /* small delay to give the pic time to read the input value */
			//vin[channel]*multiplyer to set position?
		}
		/* Stepper motor 1*/
		if (vin[0] == position[0])           				/* if the position is equal the the input then stay there*/
			location[0] = vin[0];

		else if (vin[0] > position[0])       				/* if the input is greater than the position then move forwards to that position*/
			location[0] = vin[0] - position[0];

		else if (vin[0] < position[0])  {    				/* if the input is less than the position then turn on reverse and go to that position*/
			location[0] = position[0] - vin[0];
			direction += 1;
		}

		/* Stepper motor 2*/
		if (vin[2] == position[1])           				/* if the position is equal the the input then stay there*/
			location[1] = vin[1];

		else if (vin[1] > position[1])       				/* if the input is greater than the position then move forwards to that position*/
			location[1] = vin[1] - position[1];

		else if (vin[1] < position[1])  {    				/* if the input is less than the position then turn on reverse and go to that position*/
			location[1] = position[1] - vin[1];
			direction += 2;
		}

		/* Stepper motor 3*/
		if (vin[2] == position[2])           				/* if the position is equal the the input then stay there*/
			location[2] = vin[2];

		else if (vin[2] > position[2])       				/* if the input is greater than the position then move forwards to that position*/
			location[2] = vin[2] - position[2];

		else if (vin[2] < position[2])  {    				/* if the input is less than the position then turn on reverse and go to that position*/
			location[2] = position[2] - vin[2];
			direction += 4;
		}

		/* Stepper motor 4*/
		if (vin[3] == position[3])           				/* if the position is equal the the input then stay there*/
			location[3] = vin[3];

		else if (vin[3] > position[3])       				/* if the input is greater than the position then move forwards to that position*/
			location[3] = vin[3] - position[3];

		else if (vin[3] < position[3])  {    				/* if the input is less than the position then turn on reverse and go to that position*/
			location[3] = position[3] - vin[3];
			direction += 8;
		}

		/* Stepper motor 5*/
		if (vin[4] == position[4])           				/* if the position is equal the the input then stay there*/
			location[4] = vin[4];

		else if (vin[4] > position[4])       				/* if the input is greater than the position then move forwards to that position*/
			location[4] = vin[4] - position[4];

		else if (vin[4] < position[4])  {    				/* if the input is less than the position then turn on reverse and go to that position*/
			location[4] = position[4] - vin[4];
			direction += 16;
		}

		/* Stepper motor 6*/
		if (vin[5] == position[5])           				/* if the position is equal the the input then stay there*/
			location[5] = vin[5];

		else if (vin[5] > position[5])       				/* if the input is greater than the position then move forwards to that position*/
			location[5] = vin[5] - position[5];

		else if (vin[5] < position[5])  {    				/* if the input is less than the position then turn on reverse and go to that position*/
			location[5] = position[5] - vin[5];
			direction += 32;
		}

		/* Stepper motor 7*/
		if (vin[6] == position[6])           				/* if the position is equal the the input then stay there*/
			location[6] = vin[6];

		else if (vin[6] > position[6])       				/* if the input is greater than the position then move forwards to that position*/
			location[6] = vin[6] - position[6];

		else if (vin[6] < position[6])  {    				/* if the input is less than the position then turn on reverse and go to that position*/
			location[6] = position[6] - vin[channel];
			direction += 64;
		}

		/* Fetch servo code*/
		If (vin[7] != servo_pos)
			servo();
		}

		for(step = 0; step < 100; step++){                     /*  For loop where on states occur*/   

			/* build binary index*/
			dec_bin(movement);

			/* note: we appear to test the values in bin[] backwards. 
			we can fix this later.
			*/
			if(bin[6]==1){                                /* test if active*/
				if (position[0] == location[0])               /* if the position is in the correct location turn of that pin */
					movement -= 1;                                     
				else if (position[0]>location[0])             /* if the position is beyond the location go down one step*/
					position[channel] += 1;                  
				else if (position[0]<location[0])             /* if the position is before the location move one step*/
					position[channel] -= 1;
			}

			if(bin[5]==1){                                /* test if active*/
				if (position[1] == location[1])               /* if the position is in the correct location turn of that pin */
					movement -= 2;                                     
				else if (position[1]>location[1])             /* if the position is beyond the location go down one step*/
					position[channel] += 1;                  
				else if (position[1]<location[1])             /* if the position is before the location move one step*/
					position[channel] -= 1;       
			}           

			if(bin[4]==1){                                /* test if active*/
				if (position[2] == location[2])               /* if the position is in the correct location turn of that pin */
					movement -= 4;                                     
				else if (position[2]>location[2])             /* if the position is beyond the location go down one step*/
					position[channel] += 1;                  
				else if (position[2]<location[2])             /* if the position is before the location move one step*/
					position[channel] -= 1;      
			}            

			if(bin[3]==1){                                /* test if active*/
				if (position[3] == location[3])               /* if the position is in the correct location turn of that pin */
					movement -= 8;                                     
				else if (position[3]>location[3])             /* if the position is beyond the location go down one step*/
					position[channel] += 1;                  
				else if (position[3]<location[3])             /* if the position is before the location move one step*/
					position[channel] -= 1;      
			}            

			if(bin[2]==1){                                /* test if active*/
				if (position[4] == location[4])               /* if the position is in the correct location turn of that pin */
					movement -= 16;                                     
				else if (position[4]>location[4])             /* if the position is beyond the location go down one step*/
					position[channel] += 1;                  
				else if (position[4]<location[4])             /* if the position is before the location move one step*/
					position[channel] -= 1;
			}

			if(bin[1]==1){                                /* test if active*/
				if (position[5] == location[5])               /* if the position is in the correct location turn of that pin */
					movement -= 32;                                     
				else if (position[5]>location[5])             /* if the position is beyond the location go down one step*/
					position[channel] += 1;                  
				else if (position[5]<location[5])             /* if the position is before the location move one step*/
					position[channel] -= 1;
			}

			if(bin[0]==1){                                /* test if active*/
				if (position[6] == location[6])               /* if the position is in the correct location turn of that pin */
					movement -= 64;                                     
				else if (position[6]>location[6])             /* if the position is beyond the location go down one step*/
					position[channel] += 1;                  
				else if (position[6]<location[6])             /* if the position is before the location move one step*/
					position[channel] -= 1;
			}

			output_B(direction);                            /* turn on outputs on Bank B based on binary */
			output_D(movement);                             /* turn on outputs on bank D based on binary */
			delay_ms (20);                                  /* waits so a pulse can be felt by the stepper*/
			output_D(0);                                    /* turn off all pins on bank D*/
			delay_ms (2);                                   /* needs tweeking should equal previous delay with time spent on statements above*/
		}
	}
}
          
/* servo
controls servo from input device
*/  
void servo(void)
{
	output_bit( PIN_B7, 1);
	delay_us(925);
	delay_us(vin[7]);
	delay_us(vin[7]);
	delay_us(vin[7]);
	delay_us(vin[7]);
	output_bit( PIN_B7, 0);
	servo_pos=vin[7];
}

/* dec_bin
converts a unsigned decimal integer into a decimal number

source
http://www.c.happycodings.com/Miscellaneous/code9.html

note this will load everything backwards. We can change this later.
*/
void dec_bin(unsigned int number) 
{
	int y = 0;

	for(y = 7; y >= 7; y--) {
		bin[y] = number / (1 << y);
		number -= bin[y] * (1 << y);
	}
}
