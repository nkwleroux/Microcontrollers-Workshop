/*
 * DeelB4.c
 *
 * Created: 03/2/2021 11:05:10 AM
 * Author : Nic & Jorn
 */ 

#define  F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

void wait( int ms );

int main(void)
{
	DDRD = 0b11111111;	
	PORTD = 0x01;
	while(1){
	
		for (uint8_t i=1; i<9; i++)
		{
			wait(50);
			PORTD = PORTD << 1;
		}
		PORTD = 0x01;
	}
    
}

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}


