/*
 * Delay.c
 *
 * Created: 20/3/2021 2:16:29 PM
 *  Author: Nic
 */ 

#define F_CPU 8e6
#include "Delay.h"

void wait(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}
