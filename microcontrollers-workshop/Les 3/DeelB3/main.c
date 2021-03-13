/*
 * DeelB3.c
 *
 * Created: 24/2/2021 11:33:15 AM
 * Author : Nic
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int msCounter = 0;
int switch = 0;

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void timer2Init(void){
	OCR2 = 7;
	TCCR2 = 1 << WGM21; // Clear counter on Compare match (CTC) mode (WGM21:0 = 2)
						// counter is cleared to zero when the counter value
						// TCNT2 matches OCR2.
						// WGM21 = 3;	
	
	TIMSK = TIMSK | 1<<OCIE2; //Sets the output compare match interrupt to true (enables it)
	TCCR2 |= 1<<CS22 | 0<<CS21 | 1<<CS20; //Set prescaler to clk I/O 1024 (clock select)
	TCNT2 = 0;	//Sets the value to 0;
	sei();
}

ISR( TIMER2_COMP_vect )
{
	msCounter++;
	
	if (switch && msCounter >= 25) {
		PORTD = 1<<5;
		msCounter = 0;
		switch = 0;
		
	} else if (!switch && msCounter >= 15) {
		PORTD = 0<<5;
		msCounter = 0;
		switch = 1;
	}
}

int main(void)
{
	DDRD = 0xFF;
	DDRA = 0xFF;
	timer2Init();
	
    while (1) 
    {
		PORTA = TCNT2;
		wait(50);
    }
}

