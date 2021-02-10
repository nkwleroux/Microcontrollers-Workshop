/*
 * DeelB7B.c
 *
 * Created: 10/2/2021 9:07:30 AM
 * Author : Nic
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>

void setCharliePlexingLed();
void resetLeds();
void wait();

int main(void)
{
    while (1) 
    {
		for (int i = 1; i < 7; i++)
		{
			setCharliePlexingLed(i);
			wait(250);
		}
    }
}

void setCharliePlexingLed(int lednr) {
	resetLeds();
	PORTD = 0x01;
	switch (lednr)
	{
	case 1 :
		DDRD = 0b00000011;  //0x03
		break;
	case 2 :
		DDRD = 0b00000011;  //0x03
		PORTD = PORTD << 1; //0x02
		break;
	case 3 :
		DDRD = 0b00000110;  //0x06
		PORTD = PORTD << 1; //0x02
		break;
	case 4 :
		DDRD = 0b00000110;  //0x06
		PORTD = PORTD << 2; //0x04
		break;
	case 5 :
		DDRD = 0b00000101;  //0x05
		PORTD = PORTD << 2; //0x04
		break;
	case 6 :
		DDRD = 0b00000101; //0x05
		break;
	}
}

void resetLeds() {
	DDRD = 0b00000111; //0x07
	PORTD = 0x00;
	DDRD = 0b00000000; //0x00
}

void wait( int ms ){
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}


