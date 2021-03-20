/*
 * Buzzer.c
 *
 * Created: 20/3/2021 1:28:50 PM
 *  Author: Nic
 */ 

#define F_CPU 8e6

#include "Include/Buzzer.h"

static void wait_ms(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

ISR(TIMER1_OVF_vect) {
	TCNT1H = T1HIGHCNT;
	TCNT1L = T1LOWCNT;
	if(Soundonoff == ON){
		PORTA = PORTA ^ 0x10;
	}
}

static void timer1_init(void) {
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

void buzzer_init(void){
	//Buzzer init
	timer1_init();
	PORTA = 0x00;
	DDRA = 0x10;
	EIMSK = 0x00;
	TIMSK = 0x14;
	ETIMSK = 0X00;
	sei();
}

void buzzer_sound(int freq){
	Soundonoff = ON;
	T1HIGHCNT = (0xFFFF-floor(1000000/freq)) / 0x100;
	T1LOWCNT = 0xFFFF-floor(1000000/freq) - 0xFF00;
}

void buzzer_no_sound(void){
	Soundonoff = OFF;
	wait_ms(100);
}

void buzzer_sound_Note(int tone, int dly){
	buzzer_sound(tone);
	wait_ms(dly*2);
	buzzer_no_sound();
}

void buzzer_test_sounds(void){
	buzzer_sound_Note(C1,DLY_4);
	buzzer_sound_Note(D1,DLY_4);
	buzzer_sound_Note(E1,DLY_4);
	buzzer_sound_Note(E1,DLY_4);
	buzzer_sound_Note(C1,DLY_4);
	buzzer_sound_Note(E1,DLY_4);
	buzzer_sound_Note(G1,DLY_8);
	buzzer_sound_Note(A1,DLY_8);
	buzzer_sound_Note(G1,DLY_4);
	buzzer_sound_Note(C1,DLY_4);
	buzzer_sound_Note(D1,DLY_4);
	buzzer_sound_Note(E1,DLY_4);
	buzzer_sound_Note(E1,DLY_4);
	buzzer_sound_Note(C1,DLY_4);
	buzzer_sound_Note(E1,DLY_4);
	buzzer_sound_Note(G1,DLY_8);
	buzzer_sound_Note(A1,DLY_8);
	buzzer_sound_Note(G1,DLY_4);
	buzzer_sound_Note(A1,DLY_2);
	buzzer_sound_Note(G1,DLY_4);
	buzzer_sound_Note(E1,DLY_4);
	buzzer_sound_Note(A1,DLY_2);
	buzzer_sound_Note(G1,DLY_4);
	buzzer_sound_Note(E1,DLY_4);
	buzzer_sound_Note(D1,DLY_4);
	buzzer_sound_Note(D1,DLY_4);
	buzzer_sound_Note(C1,DLY_4);
	buzzer_sound_Note(D1,DLY_4);
	buzzer_sound_Note(E1,DLY_4);
	buzzer_sound_Note(G1,DLY_4);
	buzzer_sound_Note(G1,DLY_4);
	buzzer_sound_Note(A1,DLY_4);
	buzzer_sound_Note(A1,DLY_8);
	buzzer_sound_Note(G1,DLY_4);
	buzzer_sound_Note(A1,DLY_4);
	buzzer_sound_Note(C2,DLY_4);
	buzzer_sound_Note(C2,DLY_4);
	buzzer_sound_Note(C2,DLY_4);
	buzzer_sound_Note(G1,DLY_4);
	buzzer_sound_Note(G1,DLY_4);
	buzzer_sound_Note(E1,DLY_4);
	buzzer_sound_Note(D1,DLY_4);
	buzzer_sound_Note(C1,DLY_2);
	buzzer_sound_Note(D1,DLY_4);
	buzzer_sound_Note(E1,DLY_8);
	buzzer_sound_Note(C1,DLY_4);
	buzzer_sound_Note(E1,DLY_4);
	buzzer_sound_Note(G1,DLY_4);
	buzzer_sound_Note(G1,DLY_4);
	buzzer_sound_Note(G1,DLY_4);
	buzzer_sound_Note(D1,DLY_4);
	buzzer_sound_Note(E1,DLY_8);
	buzzer_sound_Note(F1,DLY_8);
	buzzer_sound_Note(E1,DLY_4);
	buzzer_sound_Note(D1,DLY_4);
	buzzer_sound_Note(C1,DLY_2);
}
