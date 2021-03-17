/*
 * Eindopdracht_Nic_Jorn.c
 *
 * Created: 17/3/2021 9:16:11 AM
 * Author : Nic
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include "LCD/LCD.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void wait_us( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_us( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void timer1Init( void ) {
	OCR1A = 31500; // 16-bits compare value of counter 1
	TIMSK |= 1 << 4; // T1 compare match A interrupt enable
	sei(); // turn_on intr all
	TCCR1A = 0b00000000; // Initialize T1: timer, prescaler=256,
	TCCR1B = 0b00001100; // compare output disconnected, CTC, RUN
}

int sCount = 0;

ISR( TIMER1_COMPA_vect ) {
	sCount++;
}

int main(void)
{
 	init_lcd();
	wait(100);
	timer1Init();
	 
	DDRF = 0x01;
	
	display_text("init test");
	set_cursor(40);
	display_text("& wait 1 sec");
	wait(1000); //1 sec
	
	char string[10];
	int startTime,stopTime,timeDiffT;
	float rangeCm;
	 
    while (1) 
    {
		
		PORTF = 0x01; //sends a high signal
		wait_us(50); //duration of the pulse in microseconds(us)
		PORTF = 0x00; //sends a low signal
		
		while(PORTF != 0x02 ){
			lcd_clear();
				char str[10];
				sprintf(str, "%d", sCount);
				display_text(str);
				wait(1);
		}
		
		startTime = sCount;
		sCount = 0;
		
		while(PORF != 0x00);
		stopTime = sCount;
		sCount = 0;
		
		timeDiffT = stopTime - startTime;
		rangeCm = timeDiffT / 58;
		
// 		lcd_clear();
// 		dtostrf(rangeCm, 2, 2, string);/* distance to string */
// 		strcat(string, " cm   ");	/* Concat unit i.e.cm */
// 		display_text(string);
		wait(1000); //duration of the time in between the pulses in miliseconds(ms)
		
    }
}

