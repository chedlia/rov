/*   propulsion.c
	 3 Motor PWM Control with 16F877A   
*********************************************/

#include "16F877A.h"                               		/* identify pic */
#device ADC=8                                         	/* 8 bit analog capture*/
#fuses XT, PUT, NOWDT, NOPROTECT, BROWNOUT, NOCPD
#use delay(clock=4000000)                             	/* chip set at 4Mhz*/
#include "math.h" 

void main()
{
/*  Vin[0,1,2] are the variables that the potentiometer values (one for each motor)are assigned too*/
   unsigned int vin[3];
   unsigned int channel = 0;
   unsigned int speed1;
   unsigned int speed2;
   unsigned int speed3;
   unsigned int work;
   int step;                                          	/*  The step variable is used to count*/
                                                      	/*  through the for loop.  This and the */
                                                      	/*  delays will need to be tweeked to*/
                                                      	/*  enable correct duty cycle.*/
                                     
   setup_adc(ADC_CLOCK_INTERNAL);                     	/*  Setup ADC input*/
   setup_adc_ports(ALL_ANALOG);

   
   while(1)                                           	
   {
      for(channel = 0; channel <=2; channel++){			/*  setup channels*/
         set_adc_channel(channel);
         vin[channel] = read_adc();
         delay_us(10);  
      }

      work=0;											/*  reset*/

      If (vin[0] < 120)                					/*  reverse position*/
         speed1=vin[0]*-.5+80;  
      else If (vin[0] > 135){							/*  forward position*/
      work+=1;
        speed1=(vin[0]-135)*.5+20;						
         }    
      else speed1=0;									/*  stop position*/

      If (vin[1] < 120) 								/*  reverse position*/
        speed2=vin[1]*-.5+80; 
      else If (vin[1] > 135){							/*  forward position*/            
        work+=4;         
        speed2=(vin[1]-135)*.5+20;  
        }
      else speed2=0;									/*  stop position*/

      If (vin[2] < 120) 								/*  reverse position*/
        speed3=vin[2]*-.5+80;
      else If (vin[2] > 135){							/*  forward position*/ 
        work+=16;
        speed3=(vin[2]-135)*.5+20;  
        }
      else speed3=0;									/*  stop position*/

      work+=42;                                    		/*  all motor pins on*/

      for(step=0;step<100;step++)                     	/*  For loop where on states occur*/
         {
            if (speed1==step) 
               work-=2;                       			/*pin B0 off */
            if (speed2==step) 
               work-=8;                       			/*pin B3 off*/
            if (speed3==step) 
               work-=32;								/*pin B5 off*/
         
         	output_B(work);
            delay_us (2); 
         }
   }
}
