/*
 * DeelB5.c
 *
 * Created: 16/2/2021 12:27:04 PM
 * Author : Nic & Jorn
 */ 
#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"

int main(void)
{
	DDRD = 0xFF;
	init_hello_world();
	int i = 0;
    while (1) 
    {
		PORTD ^= (1<<7);	// Toggle PORTD.7
		wait( 250 );
		i++;
    }
}

