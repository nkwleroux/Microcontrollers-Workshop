/*
 * DeelB3.c
 *
 * Created: 13/3/2021 11:28:09 AM
 * Author : Nic & Jorn
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "LCD/LCD.h"

void init_adc(void){
	ADMUX = 0b11100001;		// (7,6)	11 = REFS1:0 (2.56v)
							// (5)		1 = ADLAR - left adjust result
							// (4-0)	00001 = MUX4:0 (ADC 1) 
	
	ADCSRA = 0b10000110;	// (7)		1 = ADEN (Enables ADC)
							// (6)		1 = ADSC (Single conversion mode false)
							// (5)		0 = ADFR (ADC in free running mode false)
							// (4)		0 = ADIF (ADIF interrupt disabled)
							// (3)		0 = ADIE (ADC conversion complete interrupt disabled)
							// (2-0)	110 = ADPS2:0 (64)
	wait(10);
}

int main(void)
{
	init_lcd();
	DDRF = 0x00; //input
	DDRA = 0xFF;
	DDRB = 0xFF; //output
	init_adc();

    while (1) 
    {
		ADCSRA |= 0x40; //1 << 6			
		while(ADCSRA & 0x40){		
			display_text("Loading");
			lcd_clear();
			set_cursor(0);
		}
		PORTB = ADCL;
		PORTA = ADCH; //8 bits.
		int i = ADCH + ADCL; 
		//first 8 bits
		char strADCH[12];
		sprintf(strADCH, "%d", ADCH);
		display_text(strADCH);
		set_cursor(10);
		//last 2 bits
		char strADCL[12];
		sprintf(strADCL, "%d", ADCL);
		display_text(strADCL);
		set_cursor(40);
		//combined total
		char strI[12];
		sprintf(strI, "%d", i);
		display_text(strI);
		wait(500);
		lcd_clear();
		set_cursor(0);
    }
}

