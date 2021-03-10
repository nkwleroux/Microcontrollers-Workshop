/*
 * DeelB2.c
 *
 * Created: 10/3/2021 11:42:15 AM
 * Author : Nic & Jorn
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}


void init_adc(){
	ADMUX = 0b01100011;		// (7,6)	01 = REFS1:0 (avcc with external capacitor at AREF pin)
							// (5)		1 = ADLAR - left adjust result
							// (4-0)	00011 = MUX4:0 (ADC 3) 
	
	ADCSRA = 0b11100110;	// (7)		1 = ADEN (Enables ADC)
							// (6)		1 = ADSC (Single conversion mode true)
							// (5)		1 = ADFR (ADC in free running mode)
							// (4)		0 = ADIF (ADIF interrupt disabled)
							// (3)		0 = ADIE (ADC conversion complete interrupt disabled)
							// (2-0)	110 = ADPS2:0 (64)
}

int main(void)
{
	DDRF = 0x00;
	DDRA = 0xFF;
	DDRB = 0xFF;
	init_adc();
	
    /* Replace with your application code */
    while (1) 
    {
		//PORTB = ADCL;			//If more than 8 bits are required
								//Will need to read ADCL first.
		PORTA = ADCH;
		wait(100);
    }
}



