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
	DDRD = 0xFF;
	test_hello_world();
    while (1) 
    {
		
		
    }
}

