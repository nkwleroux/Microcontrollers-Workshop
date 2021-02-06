/*
 * DeelB5.c
 *
 * Created: 2/6/2021 12:25:04 PM
 * Author : Nic & Jorn
 */ 

#define  F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

int value[25] = { 
    0x00, 0x01, 0x02, 0x04, 0x10, 0x20, 0x40, 0x80,
    0x00, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0x00,
    0x81, 0x42, 0x24, 0x18, 0x0F, 0xF0, 0x0F, 0xF0,
    0x00
};

int delay[25] = {
    100, 100, 100, 100, 100, 100, 100, 100,
    100,  50,  50,  50,  50,  50,  50, 100,
    100, 100, 100, 100, 200, 200, 200, 200,
    0x00
};

void wait( int ms ){
    for (int i=0; i<ms; i++) {
        _delay_ms( 1 );
    }
}

int main( void ){

    DDRD = 0b11111111;        

    while (1){
        int index = 0;
        int length = 25;
        
        while(index < length){
        
        PORTD = value[index];
        wait(delay[index]);
        index++;
        }
        
    }
        
}