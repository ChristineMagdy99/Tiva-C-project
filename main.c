#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "LEDs.h"
#include "delay.h"
#include "keypad.h"
#include "FSM.h"
#include "Uart.h"

void SystemInit() {}
	
// Global Variables

	 int i;
   char room_number[10];         //array to store 10 room numbers (0--> 9)
	 int current_room;            //current room's number     
   char pass_word[4];            //current room's password ( 4 characters)
	 char states [10];            //array of all room states
	 unsigned char state ;        // current room's state 
	 char passwords [10][4];      //2D array linking each room number with its 4-character-password
	
int main(void) {
	
	
	 keypad_Init();
	 LEDs_init();
	 LCD_Init();
	 Uart_init();
	
	
	while(1) {
		out_string("Enter room number ");
    current_room = (int) in_char();
		out_char((char)current_room);
    
		out_string(" Enter room_state"); 
		state = in_char();
		states[current_room] = state;
		out_char(state);
		
		if(state == '1'){                              //if check in state-->receptionist enters password
		  out_string(" Enter password"); 
		  in_string(pass_word, 3);
		  for(i=0;i<3;i++){
			passwords[current_room][i] = pass_word[i];
		  }
	  }
		
    		
		switch(state) {
			
			case '0':                                 //check out state
				check_out();                            //always locked--> solenoid always closed	
				break;
			
			case '1':                                 //check in state
			  check_in(pass_word);                    //unlocked only if correct password entered by guest
				break;
			
			case '2':                                  //room cleaning state
				room_cleaning();                        //always unlocked--> solenoid always opened
				break;
		}	
		
	}
}
