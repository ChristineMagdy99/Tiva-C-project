#include <stdint.h>
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"

#define CR   0x0D
#define BS   0x08

void Uart_init (void);
unsigned char in_char(void);
void out_char(unsigned char data);
void out_string(char *pt);
void in_string(char *bufPt, unsigned short max);
