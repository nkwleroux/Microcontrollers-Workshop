/*
 * DeelB5.c
 *
 * Created: 16/2/2021 12:27:04 PM
 * Author : Nic
 */ 
#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"

int main(void)
{
	DDRC = 0xFF;
	PORTC = 0xFF;
	init_hello_world();
    while (1) 
    {
		PORTC ^= (1<<7);	// Toggle PORTD.7
		_delay_ms( 250 );
		
    }
}

