/*
*	This code is used to convert an incomming analog voltage to a digital (binary) signal
*	The project displays this incomming voltage on a common Anode seven segment display 
*	The project uses 4MHZ Crystal. 
*	Since Proetus could not accurately simmulate in real time, the simmulation tends to 
*  	Flickir a lot. Though this problem does not persist when using real hardware components.
*	Date: SEPTEMBER 21, 2017
*	Author: ABEL ASHENAFI 
*/

#include <p18f4520.h>
#include <delays.h>
#include "prototyper.h"

#pragma config OSC = HS
#pragma config LVP = OFF
#pragma config WDT = OFF

extern volatile unsigned char ADC_Completed;

void main (void)
{
	int Merged_Value = 0;					// Variable declared to hold Merged value of ADRESH and ADRESL 
	float Real_value = 0.0;					// Variable declared to hold the real incomming floating voltage
	int Dec_Value = 0;						// Variable declared to hold A [suitable]incoming voltage's value 
	
	port_init ();							// Initializations
	ADC_Configs ();							//
	ADC_Interrupts ();						//
	Global_Interrupts ();					//
	Test_Diode ();							//
	
	while (1)
	{
		ADCON0bits.GO = 1; 					// Start the A/D conversion 
		
		if (ADC_Completed)
		{
			ADC_Completed = 0;
			
			Merged_Value = (((unsigned int)ADRESH << 8) | ADRESL);		// Performing a cast operation 
			
			Real_value = Merged_Value * 0.0048828125;    // 0.0048 is the Step Size i.e (Vref / 1024)
			Dec_Value  = Real_value * 10;		   		 // Making the incoming value suitalbe to be displayed on z 7 seg
			
			Get_Digits (Dec_Value);
		}
	}
}

