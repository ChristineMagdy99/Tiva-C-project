/********************************************************
*	
*	@LCDHardwareConnentions:
*
*  	[PB0 - PB7] ->   [BD0 - BD7]   I/O Data Bus.
*  	PA5         ->   RS            Register Select.
* 	PA6         ->   RW            Read / Write Register.
* 	PA7         ->   E             Enable Pin. 
*  
*********************************************************/
/********************************************************
*  
*		@CommandsList:
*  
*
*  Command  *  Discription         
*  ***********************************
*		0x01    *  Clear display screen
*   0x02    *  Return to home position
*   0x04    *  Shift cursor to left
*   0x06    *  Shift cursor to right
*   0x05    *  Shift display right
*   0x07    *  Shift display left
*   0x08    *  Display off, Cursor off
*   0x0A    *  Display off, Cursor on
*   0x0C    *  Display on , Cursor off
*   0x0E    *  Display on , Cursor on 
*   0x0F    *  Display on , Cursor blinking
*   0x10    *  Shift cursor position to left
*   0x14    *  Shift cursor position to right
*   0x18    *  Shift entire display to left
*   0x1C    *  Shift entire display to right
*   0x20    *  Function set : 4-bit, 1 lines, 5x7 matrix
*   0x28    *  Function set : 4-bit, 2 lines, 5x7 matrix
*   0x30    *  Function set : 8-bit, 1 lines, 5x7 matrix
*   0x38    *  Function set : 8-bit, 2 lines, 5x7 matrix
*   0x80    *  Force cursor to start from 1st line
*   0xC0    *  Force cursor to start from 2nd line
*   0x90    *  Force cursor to start from 3rd line
*   0xD0    *  Force cursor to start from 4th line
*  
********************************************************/

#include "LCD.h"


void LCD_Init(void) {
	
	/*****************************************************************************
	*  
	*		This function initialize Port A & B to control a 16x2 LCD.
	*
	* 	All used register names are predefined in the TM4C123GH6PM file.
	*	
	*****************************************************************************/
	
	// LCD ports' Initialization:
	SYSCTL_RCGCGPIO_R |= 0x03;              // Enable clock to port A & B
	while ((SYSCTL_RCGCGPIO_R&0x03)==0);    // Wait for clock to be enabled
	GPIO_PORTA_CR_R  |= 0xE0;               // Allow changes to all the bits in port A
	GPIO_PORTA_DIR_R |= 0xE0;               // Set PORTA pin 7-5 as output for control
	GPIO_PORTA_DEN_R |= 0xE0;               // Set PORTA pin 7-5 as digital pins 
	GPIO_PORTB_CR_R  |= 0xFF;               // Allow changes to all the bits in port B
	GPIO_PORTB_DIR_R |= 0xFF;               // Set all PORTB pins as output for data
	GPIO_PORTB_DEN_R |= 0xFF;               // Set all PORTB pins as digital pins

	// LCD Initialization Commands:
	delay_ms(20);
	LCD_command(FUNC_SET_8BIT_2LINE);
	delay_ms(5);
	LCD_command(FUNC_SET_8BIT_2LINE);
	delay_us(100);
	LCD_command(FUNC_SET_8BIT_2LINE);
	LCD_command(DISPLAY_OFF_CURSOR_OFF); 
	LCD_command(CLEAR_DISPLAY);            
	LCD_command(SHIFT_CURSOR_RIGHT);   
	LCD_command(DISPLAY_ON_CURSOR_ON);         
}


void LCD_command(unsigned int command) {
	
	/*****************************************************************************
	*
	*		This function, First allow data pins of the LCD to accept a command 
	*		then it sends the given command.
	*
	******************************************************************************/
	
	GPIO_PORTA_DATA_R = 0;								// Set RS to 0 to enable Command Register and RW to 0 to write to the LCD
	GPIO_PORTB_DATA_R = command;
	GPIO_PORTA_DATA_R = 0x80;
	delay_us(1);
	GPIO_PORTA_DATA_R = 0x00;              	// High to Low pulse to push the command to the LCD
	if (command < 4) 
		delay_ms(2);                  	     	// Command 1 and 2 needs up to 1.64ms 
	else             
		delay_us(40);                 	     	// All others 40 us

}


void LCD_data(unsigned char data) { 

	/*****************************************************************************
	*	
	*		This function, First allow data pins of the LCD to accept data
	*		then it sends this data.
	*
	******************************************************************************/

	GPIO_PORTA_DATA_R = 0x20;               // Set RS to 1 to enable Data Register and RW to low to write to the LCD
	GPIO_PORTB_DATA_R = data;
	GPIO_PORTA_DATA_R = 0x80 | 0x20;
	delay_us(1);
	GPIO_PORTA_DATA_R = 0;                  // High to Low pulse to push the data to the LCD
	delay_us(40);
}


void LCD_printString(char* str) {

	int i = 0;

	LCD_command(DISPLAY_ON_CURSOR_OFF);
	
	while (str[i] != '\0') {
		LCD_data(str[i]);
		i++;
	}
}



void LCD_invalid_password(void) {
	LCD_command(CLEAR_DISPLAY);
	LCD_command(HOME_POSITION);
  LCD_printString("Incorrect PW.");
	delay_s(4);
}


void LCD_welcome(void) {
	
	int i;
	for(i = 0; i < 3; i++) {
		LCD_command(CLEAR_DISPLAY);
		LCD_command(HOME_POSITION);
		LCD_printString("Safe Box Project");
		delay_ms(500);
		LCD_command(CLEAR_DISPLAY);
		delay_ms(500);
	}
}


void LCD_welcome_prompt(void) {
	LCD_command(CLEAR_DISPLAY);
	LCD_command(HOME_POSITION);
	LCD_printString("Config Mode:");
	LCD_command(CURSOR_START_2ND_LINE);
	LCD_printString("Enter PW: ");
	LCD_command(DISPLAY_ON_CURSOR_ON);
}


void LCD_prompt(void) {
	LCD_command(CLEAR_DISPLAY);
	LCD_command(HOME_POSITION);
	LCD_printString("Safe is Locked.");
	LCD_command(CURSOR_START_2ND_LINE);
	LCD_printString("Enter PW: ");
	LCD_command(DISPLAY_ON_CURSOR_ON);
}


void LCD_unlocked_prompt(void) {
	LCD_command(CLEAR_DISPLAY);
	LCD_command(HOME_POSITION);
	LCD_printString("Safe Unlocked.");
	LCD_command(CURSOR_START_2ND_LINE);
	LCD_command(DISPLAY_ON_CURSOR_ON);	
}


void LCD_cursorblink(void) {

	LCD_command(CURSOR_START_1ST_LINE);
	LCD_command(DISPLAY_ON_CURSOR_BLINK);
}


void LCD_setcursorRowCol(unsigned int row, unsigned int col) {
	
	int command = 0x00;
	
	if(row == 0) {
		command = 0x80;
		while(col <= 0x0F && col) {
		  LCD_command(command + col);
		  break;
		}
	}
	
	if(row == 1) {
		command = 0xC0;
		while(col <= 0x0F && col) {
		  LCD_command(command + col);
		  break;
		}
	}
}