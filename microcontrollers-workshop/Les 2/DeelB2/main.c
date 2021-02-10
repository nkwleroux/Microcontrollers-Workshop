/*
 * DeelB2.c
 *
 * Created: 10/2/2021 10:30:57 AM
 * Author : Nic & Jorn
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int i = 3;

ISR( INT0_vect ) {
	if(i< 8){
	i++;
	}
	PORTD |= (1<<i);
}


ISR( INT1_vect ) {
	PORTD |= (1<<3);
}

ISR( INT2_vect){
	PORTD &= ~(1<<i);
	if(i > 4){
	i--;
	}
}


int main(void)
{
	// Init I/O
	DDRD = 0xF0;
	
	EICRA |= 0x2F; //INT2 falling edge. INIT1 en INIT0 rising edge.
	EIMSK |= 0x07; //Enable INIT 0 - 2.
	
	sei();
		
    while (1) 
    {
    }
	
	return 1;
}

