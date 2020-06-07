/**********************************************************************
*  
*	@File			    LEDs.c
*
*	@Description	LEDs interface for better user experience.
*
***********************************************************************/ 

/**********************************************************************
*  
*	@ColorMap
*		
*								Color						LEDs					PORTF_DATA_R
*							
*								OFF						---						0x00
*								Red						R--						0x02
*								Blue						--B						0x04
*								Pink						R-B						0x06
*								Green						-G-						0x08
*								Yellow			         		RG-						0x0A
*								Cyan						-GB						0x0C
*								White						RGB						0x0E
*
***********************************************************************/ 

#include <stdint.h>
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"

#define red 		0x02
#define blue 		0x04
#define pink 		0x06
#define green 	0x08
#define yellow 	0x0A
#define cyan 		0x0C
#define white 	0x0E

void LEDs_init(void);
void LED_OFF(void);
void LED_ON(uint32_t color);