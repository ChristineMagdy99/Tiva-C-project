#include "Leds.h"
#include "delay.h"


void LEDs_init(void) {
	
	// 1) Enable Clock
	SYSCTL_RCGCGPIO_R |= 0x20;											// Enable Clock for Port-F
	while((SYSCTL_RCGCGPIO_R & 0x20) == 0) {}				// Wait until Clock is Activated
		
	// 2) Unlock and Allow Changes on Port-F
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   							// Unlock Port-F
  GPIO_PORTF_CR_R = 0x0E;           							// Allow changes to Port-F(1, 2 ,3)
	
	// 3) GPIO
	GPIO_PORTF_PCTL_R = 0x00;			  								// PCTL GPIO on Port-F
  GPIO_PORTF_AFSEL_R = 0x00;       								// Disable Alternate Function on Port-F

	// 4) Digital Output
	GPIO_PORTF_AMSEL_R = 0x00;        							// Disable Analog on Port-F
  GPIO_PORTF_DIR_R = 0x0E;          							// Set Port-F(1, 2 ,3) as Output
  GPIO_PORTF_DEN_R = 0x0E;          							// Enable Digital I/O on Port-F(1, 2 ,3)
		
}

void LED_OFF(void) {
		GPIO_PORTF_DATA_R = 0x00;
}

void LED_ON(uint32_t color) {
	GPIO_PORTF_DATA_R = color;
}