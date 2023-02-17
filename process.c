#include <p18f4520.h>
#include <delays.h>
#include "prototyper.h"

void Test_Diode (void)
{
	LATDbits.LATD2 	 = 1;   		// Pin used to check pwr on Ckt 
}

unsigned char Get_Digits (int Incoming_value)
{
	int msd = 0;
	int lsd = 0;
	
	msd = Incoming_value / 10;		// Get the first digit 
	lsd = Incoming_value % 10;		// Get the second digit 
	
	LATC = Display (msd); 			// Send the first digit to port c
	Digit1_Enable = 1; 				// Enable first digit 
	Delay1KTCYx(1);					// Wait for 1ms
	Digit1_Enable = 0; 				// Disable first digit	
	
	LATC = Display (lsd); 			// Send the second digit to port c
	Digit2_Enable = 1; 				// Enable second digit 
	Delay1KTCYx(1);					// Wait for 1ms
	Digit2_Enable = 0; 				// Disable second digit
	
}

unsigned char Display (unsigned char no)
{
	unsigned char pattern;
	unsigned char Segments [] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,
								0x7D,0x07,0x7F,0x6F};            // numbers from 0-9 in 7 seg 
	pattern = Segments [no];
	pattern = ~ pattern;
	return (pattern); 
}

