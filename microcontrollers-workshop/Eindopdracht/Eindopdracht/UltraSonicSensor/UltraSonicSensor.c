/*
 * UltraSonicSensor.c
 *
 * Created: 20/3/2021 3:03:33 PM
 *  Author: Nic
 */ 

#define F_CPU 8e6

#include "Include/UltraSonicSensor.h"

// int sCount = 0;
// 
// char string[10];
// int startTime,stopTime,timeDiffT;
// float rangeCm;
static void wait_us(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_us( 1 );		// library function (max 30 ms at 8MHz)
	}
}

static void wait_ms(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void ussensor_init(void){
	DDRF = 0x01;
}

void ussensor_pulse_signal(void){
	PORTF = 0x01; //sends a high signal
	wait_us(50); //duration of the pulse in microseconds(us)
	PORTF = 0x00; //sends a low signal
	
}

// ISR( TIMER1_COMPA_vect ) {
// 	sCount++;
// }

// TODO	Change TCCR1A to external clock source on falling edge.
// 		Maybe add another time for rising edge and compare the length to get the difference.
// TODO  Change to another timer. Timer 1 is already used for buzzer.
// void timer1Init(void) {
// 	OCR1A = 31500; // 16-bits compare value of counter 1
// 	TIMSK |= 1 << 4; // T1 compare match A interrupt enable
// 	sei(); // turn_on intr all
// 	TCCR1A = 0b00000000; // Initialize T1: timer, prescaler=256,
// 	TCCR1B = 0b00001100; // compare output disconnected, CTC, RUN
// }

//doesn't work
// void calculate_distance(void){
// 		while(PORTF != 0x02 ){
// 			lcd_clear();
// 			char str[10];
// 			sprintf(str, "%d", sCount);
// 			display_text(str);
// 			wait_ms(1);
// 		}
//
// 		startTime = sCount;
// 		sCount = 0;
//
// 		while(PORF != 0x00);
// 		stopTime = sCount;
// 		sCount = 0;
//
// 		timeDiffT = stopTime - startTime;
// 		rangeCm = timeDiffT / 58;
//
// 		lcd_clear();
// 		dtostrf(rangeCm, 2, 2, string);/* distance to string */
// 		strcat(string, " cm   ");	/* Concat unit i.e.cm */
// 		display_text(string);
// }