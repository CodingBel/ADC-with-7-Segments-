#include <p18f4520.h>
#include <delays.h>
#include "prototyper.h"

void port_init (void)
{
	TRISC = 0x00; 				// make all of portC output pins
	LATC  = 0x00;				// Initialize all of portc as 0s
	
	TRISAbits.TRISA0 = 1;		// Configure RA0/AN0 as an i/p pin 
	
	TRISDbits.TRISD3 = 0;		// Digit 1 enable pin 
	LATDbits.LATD3   = 0;		// Initialize Digit 1 enable pin to 0
	
	TRISDbits.TRISD4 = 0;		// Digit 2 enable pin 
	LATDbits.LATD4   = 0;		// Initialize Digit 2 enable pin to 
	
	TRISDbits.TRISD2 = 0;		// Pin used to check power on ckt
	LATDbits.LATD2 	 = 0;		// Initialize power checking pin to 0
}

void ADC_Configs (void)
{
	ADCON1bits.VCFG1 = 0;		// Choose the power supply's VSS as VREF-
	ADCON1bits.VCFG0 = 0;		// Choose the power supply's VDD as VREF+
	
	ADCON1bits.PCFG3 = 1;       // Configure RA0/AN0 as an analog pin
	ADCON1bits.PCFG2 = 1;		//
	ADCON1bits.PCFG1 = 1;		//
	ADCON1bits.PCFG0 = 0; 		//
	
	ADCON0bits.CHS3  = 0;		// Select the AN0 @RA0 as an analog input channel
	ADCON0bits.CHS2  = 0;		//
	ADCON0bits.CHS1  = 0;		//
	ADCON0bits.CHS0  = 0;		//
	
	ADCON2bits.ADFM  = 1; 		// The A/D result is right justified 
	
	ADCON2bits.ADCS2 = 0;		// Select the A/D conversion clock as FOSC/8
	ADCON2bits.ADCS1 = 0;		// To obtain a minimum and valid Tad of 2.66us
	ADCON2bits.ADCS0 = 1;		// @ an external crystal of 4MHZ
	
	ADCON2bits.ACQT2 = 1;		// Select an aquisition time of 6Tad
	ADCON2bits.ACQT1 = 0;		// i.e the aquisition time is 18us @4MHZ (Tad = 2us)
	ADCON2bits.ACQT0 = 0; 		// Rule of thumb suggests a minimum of 15us
	
	ADCON0bits.ADON  = 1; 		// The A/D converter module is enabled 
}

void ADC_Interrupts (void)
{
	PIE1bits.ADIE = 1; 			// Enable the A/D conversion interrupt
	IPR1bits.ADIP = 1;      	// Make the A/D conversion interrupt a high priority 
	PIR1bits.ADIF = 0; 			// Clear the A/D conversion interrupt Flag  
}

void Global_Interrupts (void)
{
	INTCONbits.PEIE    = 1;		// Enable peripheral interrupts 
	INTCONbits.GIE     = 1;  	// Enable interrupts globally 
}


