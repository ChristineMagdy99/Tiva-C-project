/**************************************************************************
*  
*  @File	   		delay.c
*
*  @Description Delay Functions by Seconds, Milliseconds and Microseconds.
*								Assuming Microcontroller's clock frequency is 16MHz.
*
**************************************************************************/   

#include "delay.h"

void delay_s(int time) {
	delay_ms(time * 1000);
}


void delay_ms(int time) {
	
	int i, j;
	for(i = 0 ; i < time; i++)
		for(j = 0; j < 3180; j++){}
}
 

void delay_us(int time) {
	
	int i, j;
	for(i = 0 ; i < time; i++)
		for(j = 0; j < 3; j++){}		
}