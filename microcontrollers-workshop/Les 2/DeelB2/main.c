/*
 * DeelB2.c
 *
 * Created: 10/2/2021 10:30:57 AM
 * Author : Nic
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR( INT0_vect ) {
	PORTD |= (1<<5);
}


ISR( INT1_vect ) {
	PORTD |= (1>>5);
}

ISR( INT2_vect){
	PORTD &= ~(1<<5);
}


int main(void)
{
	// Init I/O
	DDRD = 0xF0;
	
	EICRA |= 0x2F; //INT2 falling edge. INIT1 en INIT0 rising edge.
	EIMSK |= 0x07; //Enable INIT 0 - 2.
	
	sei();
		
    /* Replace with your application code */
    while (1) 
    {
    }
	//test
	return 1;
}

