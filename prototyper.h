#include <p18f4520.h>
#include <delays.h>

void port_init (void);
void ADC_Configs (void);
void ADC_Interrupts (void);
void Global_Interrupts (void);
void Test_Diode (void);
unsigned char Display (unsigned char);
unsigned char Get_Digits (int); 
void check_isr (void);


#define Digit1_Enable LATDbits.LATD3
#define Digit2_Enable LATDbits.LATD4

