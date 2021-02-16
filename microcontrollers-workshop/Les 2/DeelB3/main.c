/*
 * DeelB3.c
 *
 * Created: 10/2/2021 11:56:13 AM
 * Author : Nic & Jorn
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

const unsigned char Numbers [16] = {
	// dPgfe dcba
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01100111, // 9
	0b01110111,	// 10 (A)
	0b01111100,	// 11 (B)
	0b00111001,	// 12 (C)
	0b01011110,	// 13 (D)
	0b01111001,	// 14 (E)
	0b01110001,	// 15 (F)
			// 16 (G) Must not be displayed since its bigger than 15.
};

void display(int digit);
void wait( int ms );

int main(void)
{
	DDRC = 0b11111111;
    while (1) 
    {
		for (int i = 0; i < 16; i++)
		{
			display(i);
			
		}
    }
}

void display(int digit){
	if(0 <= digit || digit <= 15){
		PORTC= Numbers[digit];
		
	}else{
		PORTC= 0b01101111;
	}
	wait(500);
}

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}
