/*
 * DeelB3.c
 *
 * Created: 10/2/2021 11:56:13 AM
 * Author : Nic & Jorn
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

const unsigned char Numbers [10] = {
	// dPgfe dcba
	0b 0011 1111, // 0
	0b 0000 0110, // 1
	0b 0101 1011, // 2
	0b 0100 1111, // 3
	0b 0110 0110, // 4
	0b 0110 1101, // 5
	0b 0111 1101, // 6
	0b 0000 0111, // 7
	0b 0111 1111, // 8
	0b 0110 1111, // 9
};

void display(int digit);
void wait( int ms );

int main(void)
{
	PORTC = 0b11111111;
    /* Replace with your application code */
    while (1) 
    {
		for (int i; i < 10; i++;)
		{
			PORTC= Numbers[i];
			wait(100);
		}
    }
}

void display(int digit){
	if(0 <= digit || digit <= 15){
		
	}else{
		
	}
	
}

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}
