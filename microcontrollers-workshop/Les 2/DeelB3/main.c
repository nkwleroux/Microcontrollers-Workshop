/*
 * DeelB3.c
 *
 * Created: 10/2/2021 11:56:13 AM
 * Author : Nic & Jorn
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

//Array of numbers in binary.
const unsigned char Numbers [] = {
	//Pgfedcba
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
	0b01111011, // 16 (e) e for Error. Can't use E since that represents 14.
};

void display(int digit);
void wait( int ms );

int main(void)
{
	DDRC = 0b11111111; //output port c
	DDRD = 0x00; //input port D
    int i = 0; //counter
	while (1) 
    {
			if(PIND == 0b11){
				i = 0;
			}else if(PIND == 0b01){
				i++;
			}else if(PIND == 0b10){
				i--;
			}
			
			display(i);
			wait(200);
    }
}

//Displays the digit on the screen if the number is between 0 and 15.
void display(int digit){
	if(digit < 0 || digit > 15){
		PORTC = Numbers[16];
	}else{
		PORTC = Numbers[digit];
	}
}

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}
