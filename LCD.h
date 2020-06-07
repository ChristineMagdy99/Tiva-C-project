/**********************************************************************
*  
*	@File					lcd.h
*
*	@Description	Header file for LCD.c
*
***********************************************************************/  

#include <stdio.h>
#include <stdint.h>
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "delay.h"


#define  RS                       ((unsigned int)(1U << 4) 
#define  RW                       ((unsigned int)(1U << 5)
#define  EN                       ((unsigned char)(1U << 6)
#define  CLEAR_DISPLAY            ((unsigned char) 0X01 )
#define  HOME_POSITION            ((unsigned char) 0X02 )
#define  SHIFT_CURSOR_LEFT        ((unsigned char) 0X04 )
#define  SHIFT_CURSOR_RIGHT       ((unsigned char) 0X06 )
#define  SHIFT_DISPLAY_LEFT       ((unsigned char) 0X07 )
#define  SHIFT_DISPLAY_RIGHT      ((unsigned char) 0X05 )
#define  DISPLAY_OFF_CURSOR_OFF   ((unsigned char) 0X08 )
#define  DISPLAY_OFF_CURSOR_ON    ((unsigned char) 0X0A )
#define  DISPLAY_ON_CURSOR_OFF    ((unsigned char) 0X0C )
#define  DISPLAY_ON_CURSOR_ON     ((unsigned char) 0X0E )
#define  DISPLAY_ON_CURSOR_BLINK  ((unsigned char) 0X0F )
#define  FUNC_SET_4BIT_1LINE      ((unsigned char) 0X020)
#define  FUNC_SET_4BIT_2LINE      ((unsigned char) 0X028)
#define  FUNC_SET_8BIT_1LINE      ((unsigned char) 0X030)
#define  FUNC_SET_8BIT_2LINE      ((unsigned char) 0X038)
#define  CURSOR_START_1ST_LINE    ((unsigned char) 0X80 )
#define  CURSOR_START_2ND_LINE    ((unsigned char) 0XC0 )


void LCD_Init              (void);
void LCD_command           (unsigned int);
void LCD_data              (unsigned char);
void LCD_printString       (char*);
void LCD_invalid_password  (void);
void LCD_welcome_prompt		 (void);
void LCD_prompt						 (void);
void LCD_unlocked_prompt	 (void);
void LCD_welcome					 (void);
void LCD_setcursorRowCol   (unsigned int, unsigned int);