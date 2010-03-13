#import <stdio.h>
#import <stdlib.h>

#include "16F877A.h"
#device ADC=8
#use delay(clock=8000000)

const unsigned int NUM_MOTORS = 3;

typedef struct motor_info {
	unsigned int data;
	unsigned int pina;
	unsigned int pinb;
	//unsigned int ontime; //is this needed?
	//other stuff?
} motor_data;

static void sort(motor_data *motor[]);
static void initilize(motor_data *motor[]);
static void readADC(motor_data *motor[]);

main(){
	motor_data *motor[NUM_MOTORS];
	initilize(motor);
	
	while(1){
		readADC(motor);
		sort(motor);
	}
}

//sorts the array smallest to largest
void sort(motor_data *motor[]){
	int x = 0;
	motor_data *swap;
	
	while(++x<NUM_MOTORS){ //sort the array
		if((*motor[x-1]).data > (*motor[x]).data){ 
			swap = motor[x];
			motor[x] = motor[x-1];
			motor[x-1] = swap;
			x = 0;
		}
	}
}

//initilize	the constants
void initilize(motor_data *motor[]){
	int x = 0;
	
	for (x = 0; x < NUM_MOTORS; x++) //initilize and set some values
		motor[x] = malloc(sizeof(motor_data));
	(*motor[0]).pina = PIN_B0;
	(*motor[0]).pinb = PIN_B1;
	
	(*motor[1]).pina = PIN_B2;
	(*motor[1]).pinb = PIN_B3;
	
	(*motor[2]).pina = PIN_B4;
	(*motor[2]).pinb = PIN_B5;
}

static void readADC(motor_data *motor[]){
	//in this case ADC channels are 0,1,2... may not be in other microcontrollers
	int channel;
	for(channel = 0; channel < NUM_MOTORS; channel++){
		set_adc_channel(channel);
		(*motor[channel]).data = read_adc();
		delay_ms(10); //need to delay a little to get a good reading
	}
}