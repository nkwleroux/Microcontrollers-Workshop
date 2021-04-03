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
#include "Include/Buzzer.h"

static void wait_ms(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

ISR(TIMER3_OVF_vect) {
	TCNT3H = T3HIGHCNT;
	TCNT3L = T3LOWCNT;
	if(Soundonoff == ON){
		PORTA = PORTA ^ 0x10;
	}
}

//todo
void init_Buzzer(void){
	//Buzzer init
	timer3_init();
	PORTA = 0x00;
	DDRA = 0x10;
	EIMSK = 0x00;
	ETIMSK = 0x00;
	ETIMSK = 0x14; 
	sei();
}

void timer3_init(void) {
	TCCR3B = 0x00;
	
	//Gives access to read and write operations.
	TCNT3H = T1HIGHCNT;
	TCNT3L = T1LOWCNT;
	
	//High byte must be written to before low byte.
	OCR3AH = 0x02; 
	OCR3AL = 0x9A;
	
	ICR3H = 0x02;
	ICR3L = 0x9A;
	
	TCCR3A = 0x00; 
	TCCR3B = 0x02; // Prescaler 8
}

void sound(int freq){
	Soundonoff = ON;
	T3HIGHCNT = (0xFFFF-floor(1000000/freq)) / 0x100;
	T3LOWCNT = 0xFFFF-floor(1000000/freq) - 0xFF00;
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
// 	soundNote(A1,DLY_8);
// 	soundNote(G1,DLY_4);
// 	soundNote(C1,DLY_4);
// 	soundNote(D1,DLY_4);
// 	soundNote(E1,DLY_4);
// 	soundNote(E1,DLY_4);
// 	soundNote(C1,DLY_4);
// 	soundNote(E1,DLY_4);
// 	soundNote(G1,DLY_8);
// 	soundNote(A1,DLY_8);
// 	soundNote(G1,DLY_4);
// 	soundNote(A1,DLY_2);
// 	soundNote(G1,DLY_4);
// 	soundNote(E1,DLY_4);
// 	soundNote(A1,DLY_2);
// 	soundNote(G1,DLY_4);
// 	soundNote(E1,DLY_4);
// 	soundNote(D1,DLY_4);
// 	soundNote(D1,DLY_4);
// 	soundNote(C1,DLY_4);
// 	soundNote(D1,DLY_4);
// 	soundNote(E1,DLY_4);
// 	soundNote(G1,DLY_4);
// 	soundNote(G1,DLY_4);
// 	soundNote(A1,DLY_4);
// 	soundNote(A1,DLY_8);
// 	soundNote(G1,DLY_4);
// 	soundNote(A1,DLY_4);
// 	soundNote(C2,DLY_4);
// 	soundNote(C2,DLY_4);
// 	soundNote(C2,DLY_4);
// 	soundNote(G1,DLY_4);
// 	soundNote(G1,DLY_4);
// 	soundNote(E1,DLY_4);
// 	soundNote(D1,DLY_4);
// 	soundNote(C1,DLY_2);
// 	soundNote(D1,DLY_4);
// 	soundNote(E1,DLY_8);
// 	soundNote(C1,DLY_4);
// 	soundNote(E1,DLY_4);
// 	soundNote(G1,DLY_4);
// 	soundNote(G1,DLY_4);
// 	soundNote(G1,DLY_4);
// 	soundNote(D1,DLY_4);
// 	soundNote(E1,DLY_8);
// 	soundNote(F1,DLY_8);
// 	soundNote(E1,DLY_4);
// 	soundNote(D1,DLY_4);
// 	soundNote(C1,DLY_2);
}

void test_sounds2(void){
	soundNote(N_D3,DLY_8);
	soundNote(N_D3,DLY_8);
	soundNote(C1,DLY_8);
	soundNote(N_D4,DLY_4);
	soundNote(D2,DLY_8);
	soundNote(N_A3,DLY_3);
	wait_ms(DLY_32);
	soundNote(N_GS3,DLY_4);
	soundNote(D1,DLY_8);
	soundNote(N_G3,DLY_4);
	soundNote(N_F3,DLY_4);
	soundNote(A1,DLY_8);
	soundNote(N_D3,DLY_8);
	soundNote(N_F3,DLY_8);
	soundNote(N_G3,DLY_8);
	soundNote(N_C3,DLY_8);
	soundNote(N_C3,DLY_8);
	soundNote(N_D4,DLY_4);
	soundNote(N_A3,DLY_3);
}
