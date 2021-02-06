/*
 * DeelB6.c
 *
 * Created: 06/2/2021 12:33:40 PM
 * Author : Nic & Jorn
 */ 

#define  F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

typedef enum { false, true } bool;

void wait( int ms ){
    for (int i=0; i<ms; i++) {
        _delay_ms( 1 );
    }
}

int main( void ){

    DDRD = 0b11111111;   
	int buttonPress = 2;      

    while (1){
        
        if(PINC & 0x01){
			buttonPress++;
        };
        
        if(buttonPress % 2 == 0){
			PORTD = 0x80;
			wait(1000);
			PORTD = 0x00;
			wait(1000);
        };
        
        if(buttonPress % 2 == 1){
			PORTD = 0x80;
			wait(4000);
			PORTD = 0x00;
			wait(4000);
        };
        
    }
        
}
