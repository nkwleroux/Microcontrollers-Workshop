/*
 * DeelB.c
 *
 * Created: 03/2/2021 11:05:10 AM
 * Author : Nic & Jorn
 */ 

#define  F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

void wait( int ms );

int main(void)
{
	DDRD = 0b11111111;	
	
    while (1) 
    {
		PORTD = 0x40;			// write 10000000b
		wait( 500 );
		PORTD = 0x80;			// Write 01000000b PORTD
		wait( 500 );
    }
}

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

