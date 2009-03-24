#import <stdio.h>
#import <stdlib.h>

const int NUM_MOTORS = 4;

typedef struct motor_info {
	int data;
	//other stuff
} motor_data;

/*

#include "16F877A.h"
#device ADC=8
 
#use delay(clock=8000000)

const int NUM_MOTORS = 3;

typedef enum _MOTOR_STATE
{
	UNDEFINED,
	SET_HIGH,
	SET_LOW
} MOTOR_STATE, *PMOTOR_STATE;

typedef struct _MOTOR
{
	unsigned int vin;

	unsigned int reverse;
	unsigned int rev_pin;
	MOTOR_STATE prev_rev_state;

	unsigned int forward;
	unsigned int fwd_pin;
	MOTOR_STATE prev_fwd_state;
} MOTOR, *PMOTOR;
*/



int main(){
	int len = NUM_MOTORS;
	motor_data *myArray[len];
	motor_data *swap;
	int x = 0;
	
	for (x = len-1; x >= 0; x--){ //initilize and set some values
		myArray[x] = malloc(sizeof(motor_data));
		(*myArray[x]).data = x*-1;
	}
	
	
	printf("array before sort:\n");
	for (x = 0; x < len; x++)
		printf("%i\n", (*myArray[x]).data);
	
	x = 0;
	while(++x<len){ //sort za array!
		if((*myArray[x-1]).data > (*myArray[x]).data){
			swap = myArray[x];
			myArray[x] = myArray[x-1];
			myArray[x-1] = swap;
			x = 0;
		}
	}
	
	printf("\narray after sort:\n");
	for (x = 0; x < len; x++)
		printf("%i\n", (*myArray[x]).data);
		
	for (x = 0; x < len; x++)
		free(myArray[x]); //free up memory so there are no memory leaks
		
	return 0;
}