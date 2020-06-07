#include "FSM.h"



void check_out(void) { 
  
	   // LED
	      LED_ON(red);                            //always locked-->solenoid always closed
		 // prompt to receptionist
	      out_string("Room is free");
}




void get_password(char *pw_str) {
	
	int i, ch;
	for(i = 0; i < PASSWORD_SIZE; i++) {

		// Get char from keypad and store it in pw_str
		ch = keypad_getkey();
		
	 //save this character in the password array of chars
		pw_str[i] = ch;

  	}
		
	}




void check_in(char *password) {
	
	char pw_str[4];                                   //password input by user, received from keypad
	int i, lockout_counter = 0, correct_pw = 0;
	
	

	
	// LEDs
	LED_ON(red);	                                   //correct password hasn't been entered yet
                                                   //solenoid still closed
	delay_ms(500);
	while(!correct_pw) {	
		
				
		// Keypad
		// Get New Password
		get_password(pw_str);                       
		
		
	
		// Check Password
		correct_pw = 1;
		for(i = 0; i < PASSWORD_SIZE; i++) {                //compare password input by guest with 
			if(pw_str[i] != password[i]) {                    // password set by receptionist to this room
				correct_pw = 0;
			}
		}
		
		// Correct Password
		if(correct_pw) {                                   //guest enetered correct password
			// LED
	     LED_ON(green);                                  //led turns green--> solenoid opens
			
			
			//receptionist prompt
			out_string("Room has been successfully opened");
			return;
		}
		
		// Incorrect Password
			else {   
				out_string("Incorrect room accessing"); 
			}
	}		
}

void room_cleaning (void){

	
	 // LED
	      LED_ON(green);                            //always unlocked-->solenoid always open
	 // prompt to receptionist
	      out_string("Room is being cleaned");

	
}

	
	