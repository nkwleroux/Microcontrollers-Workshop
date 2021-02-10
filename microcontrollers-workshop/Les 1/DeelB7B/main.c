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
		for (int i = 0; i < 6; i++)
		{
			setCharliePlexingLed(i);
			wait(250);
		}
		resetLeds(); // resets leds.
		wait(1000); // waits 1000 miliseconds.
    }
}

// Switch case which sets the selected led and configures the pins accordingly.
void setCharliePlexingLed(int lednr) {
	resetLeds();
	PORTD = 0x01;
	switch (lednr)
	{
	case 1 :
		DDRD = 0b00000011;
		break;
	case 2 :
		DDRD = 0b00000011;
		PORTD = PORTD >> 1;
		break;
	case 3 :
		DDRD = 0b00000110;
		PORTD = PORTD >> 1;
		break;
	case 4 :
		DDRD = 0b00000110;
		PORTD = PORTD >> 2;
		break;
	case 5 :
		DDRD = 0b00000101;
		PORTD = PORTD >> 2;
		break;
	case 6 :
		DDRD = 0b00000101;
		break;
	}
}

// Turns all the leds off.
void resetLeds() {
	DDRD = 0b00000111;
	PORTD = 0x00;
	DDRD = 0b00000000;
}

void wait( int ms ){
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}


