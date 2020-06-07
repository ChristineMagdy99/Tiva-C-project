/****************************************************************************************************************
*		@Keypad
*				- Keypads are organized in a matrix of rows and columns. 
*				- When a key is pressed, a row and a column make a contact.
*				- Otherwise, there is no connection between rows and columns. 
*		
*		@KeypadConnections
*				-	The rows 		(D0 -> D3) are connected to an output port.
*				- The columns	(D4 -> D6) are connected to an input port.
*				- All the input pins have pull-up resistor connected.
*				
*		@KeyPressDetection
*				- To detect the key pressed, the microcontroller drives all rows low, then it reads the columns.
*				- If the data read from the columns is D7 -> D4 = 1111, then no key has been pressed.
*
*		@HardwareConnentions
*
* 			[PE1 - PE4] -> [R1 - R4]  Rows
* 			[PC4 - PC6] -> [C1 - C3]  Cols
*  
****************************************************************************************************************/

#include "keypad.h"
#include "delay.h"
                                                                  
unsigned const char symbol[4][3] = {{'1', '2', '3'},      
                                    {'4', '5', '6'},      
                                    {'7', '8', '9'},      
                                    {'*', '0', '#'}}; 


void keypad_Init(void) {
	
	/*****************************************************************************
	*
	*	@Description		This function initialize port-C and port-E. 
	*
	*									RCGCGPIO:	F	E	D	C	B	A	
	*														0	1	0	1	0	0				= 0x14
	*
	*									PORT-C:		7	6	5	4	3	2	1	0
	*														0	1	1	1	0	0	0	0		= 0x70
	*
	*									PORT-E:		7	6	5	4	3	2	1	0
	*														0	0	0	1	1	1	1	0		=	0x1E
	*
	****************************************************************************/	
	
  SYSCTL_RCGCGPIO_R |= 0x14;									// Enable clock for port C & E  
  while ((SYSCTL_RCGCGPIO_R & 0x14) == 0) {}	// Wait for clock to be enabled
	
  GPIO_PORTC_CR_R  |= 0x70;        		      	// Allow changes to all the bits in port C
  GPIO_PORTE_CR_R  |= 0x1E;      		        	// Allow changes to all the bits in port E
	
  GPIO_PORTC_DIR_R |= 0x70;      		        	// set directions of cols are o/ps
  GPIO_PORTE_DIR_R |= 0x00;     		        	// set directions of rows are i/ps
	
  GPIO_PORTE_PDR_R |= 0x1E;      		        	// Pull-down resistor on rows
	
  GPIO_PORTC_DEN_R |= 0x70;      		        	// Digital enable pins in port C
  GPIO_PORTE_DEN_R |= 0x1E;       		     	  // Digital enable pins in port E
	
}		


char keypad_getkey(void) {
	
	int col, row;
  while(1) {
		
    for(col = 0; col < 4; col++) {
      GPIO_PORTC_DATA_R = (1U << (col + 4));
      delay_us(2);
      
			for(row = 0; row < 4; row++) {
        if((GPIO_PORTE_DATA_R & 0x1E) & (1U << ( row + 1))) {
          return symbol[row][col];
				}
      }
    }
  }
}