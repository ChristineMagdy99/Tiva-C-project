#include "LEDs.h"
#include "delay.h"
#include "keypad.h"
#include "LCD.h"
#include "Uart.h"


#define PASSWORD_SIZE 4

/***********
Identifing states numbers received from receptionist:

	check_out	(room free )    	= 0
	check_in   (room occupied) 	= 1
	room_cleaning	            	= 2

***********/

void safe_lockout			(void);
void get_password			(char *pw_str);
void check_out(void);
void check_in(char *password);
void room_cleaning (void);