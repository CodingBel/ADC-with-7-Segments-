#include <p18f4520.h>
#include <delays.h>
#include "prototyper.h"

volatile unsigned char ADC_Completed = 0;

#pragma code MY_INTR = 0x08  				// Adress of the high priority interrupt 
void MY_INTR (void)
{
	_asm
		GOTO check_isr
	_endasm 	
}
#pragma code 

#pragma interrupt check_isr

void check_isr (void)
{
	if (PIR1bits.ADIF)						// If A/D conversion has completed  
	{
		PIR1bits.ADIF = 0;
		ADC_Completed = 1; 					
	}
}



