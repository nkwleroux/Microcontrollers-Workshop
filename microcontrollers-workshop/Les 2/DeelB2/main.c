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
	//if(i< 8){
	//i++;
	//}
	//PORTD |= (1<<i);
}


ISR( INT1_vect ) {
	if(i< 8){
		i++;
	}
	PORTD |= (1<<i);
	//PORTD &= ~(1<<i);
	//if(i > 3){
	//	i--;
	//}
}

ISR( INT2_vect){
//	PORTD &= ~(1<<0);
	PORTD &= ~(1<<i);
	if(i > 3){
		i--;
	}
}


int main(void)
{
	// Init I/O
	DDRD = 0xF0;
	
	EICRA |= 0x2C; //INT2 falling edge. INIT1 rising edge. //dit zijn de pins op de atmega128 chip. kijk in de atmega manual.
	EIMSK |= 0x06; //Enable INIT 1 - 2. (0x06) = INIT 1-2, (0x07) = INIT 0-2.
	
	sei();
		
    while (1) 
    {
    }
	
	return 1;
}

