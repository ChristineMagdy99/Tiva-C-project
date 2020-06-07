#include "Uart.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"


void Uart_init (void){

  SYSCTL_RCGCUART_R |=0x01;          //enable UART0
	SYSCTL_RCGCGPIO_R |= 0x01;        //enable port A
	GPIO_PORTA_LOCK_R = 0x4C4F434B;   //unlock PORT A
	UART0_CTL_R       &= ~(0x01);     //enable UART0
	UART0_IBRD_R      |= 8;        //int((16*10^6)/16*115200 )clock used 16MHZ
	UART0_FBRD_R      |= 44;       //setting baud rate
	UART0_LCRH_R      |= 0x0070;   //adjusting line control
	UART0_CTL_R	        |= 0x0301;   //enable uart (recieve) 
	GPIO_PORTA_AFSEL_R  |= 0x03;     //enable alternate functions for pins 0 and 1
	GPIO_PORTA_PCTL_R   = (GPIO_PORTA_PCTL_R & 0xFFFFFF00)| 0X11; //select alternate function for pin0 and pin1 (uart) 
	GPIO_PORTA_DEN_R    |=0x03;      //enable digital mode
	GPIO_PORTA_AMSEL_R  &=~(0x03);   //diasble analoge mode

}

unsigned char in_char (void){                           //reading a char

   while((UART0_FR_R & 0x0010)!=0);
	 return ((unsigned char)(UART0_DR_R & 0xFF)) ;
}

void out_char (unsigned char data){                      //writing a char
   while((UART0_FR_R & 0x0020)!=0);
	 UART0_DR_R = data;
	
}

void out_string(char *pt){                              //writing a string
  while(*pt){
    out_char(*pt);
    pt++;
  }
}

void in_string(char *bufPt, unsigned short max) {   //reading a string
int length=0;
char character;
  character = in_char();
  while(character != CR){
    if(character == BS){
      if(length){
        bufPt--;
        length--;
        out_char(BS);
      }
    }
    else if(length < max){
      *bufPt = character;
      bufPt++;
      length++;
      out_char(character);
    }
    character = in_char();
  }
  *bufPt = 0;
}
