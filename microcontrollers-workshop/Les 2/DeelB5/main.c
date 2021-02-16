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
    while (1) 
    {
		DDRA = 0xFF;
		PORTA = 0x01;
		init();
    }
}

