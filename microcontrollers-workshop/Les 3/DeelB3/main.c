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

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

// ISR( INT0_vect ) {
// 	PORTD ^= (1<<5);
	//wait(15);
	//PORTD ^= (1<<5);
// }

//ISR( INT1_vect){
// 	PORTD ^= (1<<5);
// 	wait(25);
// 	PORTD ^= (1<<5);
//}

void timer1Init( void ) {
	OCR1A = 31500;			// 16-bits compare value of counter 1
	TIMSK |= (1<<4);		// T1 compare match A interrupt enable
	sei();					// turn_on intr all	TCCR1A = 0b00000000;  Initialize T1: timer, prescaler=256,
	TCCR1B = 0b00001100;	// compare output disconnected, CTC, RUN
}

ISR( TIMER1_COMPA_vect ) {
 	PORTD ^= (1<<5);					// Toggle bit 5 van PORTD
	wait(15);
	PORTD ^= (1<<5);	
	wait(25);
}

int main(void)
{
	DDRD = 0xF0;
	DDRA = 0xff;
	
	timer1Init();
	
	//00 10 11 00 = nothing, falling edge, rising edge, nothing - 0x2c
	//00 00 10 11 = nothing, nothing, falling edge, rising edge - 0xb
	//EICRA |= 0x0b; //dit zijn de pins op de atmega128 chip. kijk in de atmega handeleiding.
	//EIMSK |= 0x03; //Enable INIT 0 - 2. (0x06) = INIT 1-2, (0x07) = INIT 0-2.
	
	//sei();
	
    /* Replace with your application code */
    while (1) 
    {
		PORTA = TCNT1;
		wait(50);
    }
}

