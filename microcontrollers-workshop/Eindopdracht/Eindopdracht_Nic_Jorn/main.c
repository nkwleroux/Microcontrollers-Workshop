/*
 * Eindopdracht_Nic_Jorn.c
 *
 * Created: 17/3/2021 9:16:11 AM
 * Author : Nic
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include "LCD/LCD.h"
#include "DeleteAfterUse/TestBuzzer.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define TRIG 1
#define ECHO 0

// void wait_us(int ms) {
// 	for (int i=0; i<ms; i++) {
// 		_delay_us( 1 );		// library function (max 30 ms at 8MHz)
// 	}
//

//todo	Change TCCR1A to external clock source on falling edge. 
//		Maybe add another time for rising edge and compare the length to get the difference.
void timer1Init(void) {
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

void timer0Init(void){
	OCR0 = 128;				//Value in which TCNT0 will be compared to. (randomly chosen)
	TIMSK = TIMSK | 1 << OCIE0;	//Timer/Counter0 Output Compare Match Interrupt Enable
	sei();					//Enable global interrupts (not sure if needed more than once) 
	TCCR0= 0b01111101;		//0		= Force Output Compare (false)
							//1..1	= Waveform Generation Mode (fast pwm [creates high frequency])
							//.11.	= Compare Match Output Mode (set OC0 on compare match, clear OC0 at BOTTOM)
							//101	= Clock Select (clkTOS/128)
	TCNT0 = 0;
}

ISR( TIMER0_COMP_vect ){
	
	
	
	
}

int msCounter = 0;

ISR( TIMER2_COMP_vect )
{
	msCounter++;
}

void timer2Init(void){
	OCR2 = 7;	//7 bits
// 	TCCR2 = 1 << WGM21; // Clear counter on Compare match (CTC) mode (WGM21:0 = 2)
// 						// counter is cleared to zero when the counter value
// 						// TCNT2 matches OCR2.
// 						// WGM21 = 3;

	TCCR2 |= 1 << WGM21 | 1 << WGM20;	// Waveform Generation Mode (Fast PWM)
		
	TIMSK = TIMSK | 1<<OCIE2; //Sets the output compare match interrupt to true (enables it)
	TCCR2 |= 1<<CS22 | 0<<CS21 | 1<<CS20; //Set prescaler to clk I/O 1024 (clock select)
	TCNT2 = 0;	//Sets the value to 0;
	sei();
}

char string[10];
int startTime,stopTime,timeDiffT;
float rangeCm;

//doesn't work
void calculate_distance(void){
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

		lcd_clear();
		dtostrf(rangeCm, 2, 2, string);/* distance to string */
		strcat(string, " cm   ");	/* Concat unit i.e.cm */
		display_text(string);
}

//Don't use DDRC because the LCD uses it.
int main(void)
{
 	init_lcd();
	wait(100);
	
/*	timer1Init();*/
/*	wait(100);*/
/*	timer0Init();*/
/*	timer2Init();*/
	 
	//DDRF = 0x01;
	//DDRA = 0xFF;
	
	//DeleteAfterUse init
	timer1_init();
	PORTG = 0x00;
	DDRG = 0x10;
	EIMSK = 0x00;
	TIMSK = 0x14; 
	ETIMSK = 0X00;
	sei();
	 
    while (1) 
    {
		//start code for sensor
		
		//PORTF = 0x01; //sends a high signal
		//wait_us(50); //duration of the pulse in microseconds(us)
		//PORTF = 0x00; //sends a low signal
		
		/*		calculate_distance();*/
		
		//end code for sensor
		
		//start code for buzzer
		
// 		PORTA = 0x03;
// 		wait(20);
// 		PORTA = 0x00;
// 		PORTA = TCNT2;
// 		wait(100);

		
// 		lcd_clear();
// 		dtostrf(TCNT0, 2, 2, string);/* distance to string */
// 		strcat(string, " timer0");	/* Concat unit i.e.cm */
// 		display_text(string);

		//end code for buzzer
		
		
		
		SoundNotice();


		wait(1000); //duration of the time in between the pulses in miliseconds(ms)
		
    }
}

