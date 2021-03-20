/*
 * Buzzer.c
 *
 * Created: 20/3/2021 1:28:50 PM
 *  Author: Nic
 */ 
#define F_CPU 8e6

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include <math.h>
#include "Buzzer.h"
#include "Delay/Delay.h"

ISR(TIMER1_OVF_vect) {
	TCNT1H = T1HIGHCNT;
	TCNT1L = T1LOWCNT;
	if(Soundonoff == ON){
		PORTA = PORTA ^ 0x10;
	}
}

void init_Buzzer(void){
	//Buzzer init
	timer1_init();
	PORTA = 0x00;
	DDRA = 0x10;
	EIMSK = 0x00;
	TIMSK = 0x14;
	ETIMSK = 0X00;
	sei();
}

void timer1_init(void) {
	TCCR1B = 0x00;
	
	TCNT1H = T1HIGHCNT;
	TCNT1L = T1LOWCNT;
	
	OCR1AH = 0x02;
	OCR1AL = 0x9A;
	
	OCR1BH = 0x02;
	OCR1BL = 0x9A;
	
	OCR1CH = 0x02;
	OCR1CL = 0x9A;
	
	ICR1H = 0x02;
	ICR1L = 0x9A;
	
	TCCR1A = 0x00;
	TCCR1B = 0x02;
}

void sound(int freq){
	Soundonoff = ON;
	T1HIGHCNT = (0xFFFF-floor(1000000/freq)) / 0x100;
	T1LOWCNT = 0xFFFF-floor(1000000/freq) - 0xFF00;
}

void nosound(void){
	Soundonoff = OFF;
	wait_ms(100);
}

void soundNote(int tone, int dly){
	sound(tone);
	wait_ms(dly*2);
	nosound();
}

void test_sounds(void){
	soundNote(C1,DLY_4);
	soundNote(D1,DLY_4);
	soundNote(E1,DLY_4);
	soundNote(E1,DLY_4);
	soundNote(C1,DLY_4);
	soundNote(E1,DLY_4);
	soundNote(G1,DLY_8);
	soundNote(A1,DLY_8);
	soundNote(G1,DLY_4);
	soundNote(C1,DLY_4);
	soundNote(D1,DLY_4);
	soundNote(E1,DLY_4);
	soundNote(E1,DLY_4);
	soundNote(C1,DLY_4);
	soundNote(E1,DLY_4);
	soundNote(G1,DLY_8);
	soundNote(A1,DLY_8);
	soundNote(G1,DLY_4);
	soundNote(A1,DLY_2);
	soundNote(G1,DLY_4);
	soundNote(E1,DLY_4);
	soundNote(A1,DLY_2);
	soundNote(G1,DLY_4);
	soundNote(E1,DLY_4);
	soundNote(D1,DLY_4);
	soundNote(D1,DLY_4);
	soundNote(C1,DLY_4);
	soundNote(D1,DLY_4);
	soundNote(E1,DLY_4);
	soundNote(G1,DLY_4);
	soundNote(G1,DLY_4);
	soundNote(A1,DLY_4);
	soundNote(A1,DLY_8);
	soundNote(G1,DLY_4);
	soundNote(A1,DLY_4);
	soundNote(C2,DLY_4);
	soundNote(C2,DLY_4);
	soundNote(C2,DLY_4);
	soundNote(G1,DLY_4);
	soundNote(G1,DLY_4);
	soundNote(E1,DLY_4);
	soundNote(D1,DLY_4);
	soundNote(C1,DLY_2);
	soundNote(D1,DLY_4);
	soundNote(E1,DLY_8);
	soundNote(C1,DLY_4);
	soundNote(E1,DLY_4);
	soundNote(G1,DLY_4);
	soundNote(G1,DLY_4);
	soundNote(G1,DLY_4);
	soundNote(D1,DLY_4);
	soundNote(E1,DLY_8);
	soundNote(F1,DLY_8);
	soundNote(E1,DLY_4);
	soundNote(D1,DLY_4);
	soundNote(C1,DLY_2);
}
