/*
 * Buzzer.c
 *
 * Created: 20/3/2021 1:28:50 PM
 *  Author: Nic & Jorn
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

//Timer 3
ISR(TIMER3_OVF_vect) {
	TCNT3H = T3HIGHCNT;
	TCNT3L = T3LOWCNT;
	if(soundState == ON){
		PORTA = PORTA ^ 0x10;
	}
}

//Initializes timer 3 
void timer3_init(void) {
	TCCR3B = 0x00;
	
	//Gives access to read and write operations.
	TCNT3H = T3HIGHCNT;	//Timer/Counter3 High
	TCNT3L = T3LOWCNT;	//Timer/Counter3 Low
	
	//High byte must be written to before low byte.
	//Used to generate an output compare interrupt.
	OCR3AH = 0x02;	//Output Compare Register 3 A High
	OCR3AL = 0x9A;	//Output Compare Register 3 A Low
	
	ICR3H = 0x02;	//Input Capture Register 3 High
	ICR3L = 0x9A;	//Input Capture Register 3 Low
	
	TCCR3A = 0x00;	//Timer/Counter3 Control Register A
	TCCR3B = 0x02;	//Timer/Counter3 Control Register B - clkI/O 8 (From prescaler)
}

//Initializes the buzzer
void buzzer_init(void){
	timer3_init();
	DDRA = 0x10;
	PORTA = 0x00;
	EIMSK = 0x00;
	ETIMSK = 0x00;
	ETIMSK = 0x14;
	sei();
}

//Turns of the buzzer.
void buzzer_sound_off(void){
	soundState = OFF;
	wait_ms(100);
}

//Used to set the frequency of the buzzer.
void buzzer_sound(int freq){
	soundState = ON;
	T3HIGHCNT = (0xFFFF-floor(1000000/freq)) / 0x100;
	T3LOWCNT = 0xFFFF-floor(1000000/freq) - 0xFF00;
}

//Used to produce a specific note.
void buzzer_sound_note(int tone, int dly){
	buzzer_sound(tone);
	wait_ms(dly*2);
	buzzer_sound_off();
}

//Plays a short song
void buzzer_play_song(void){
	buzzer_sound_note(N_D3,DLY_8);
	buzzer_sound_note(N_D3,DLY_8);
	buzzer_sound_note(N_C5,DLY_8);
	buzzer_sound_note(N_D4,DLY_4);
	buzzer_sound_note(N_D6,DLY_8);
	buzzer_sound_note(N_A3,DLY_3);
	wait_ms(DLY_32);
	buzzer_sound_note(N_GS3,DLY_4);
	buzzer_sound_note(N_D5,DLY_8);
	buzzer_sound_note(N_G3,DLY_4);
	buzzer_sound_note(N_F3,DLY_4);
	buzzer_sound_note(N_A5,DLY_8);
	buzzer_sound_note(N_D3,DLY_8);
	buzzer_sound_note(N_F3,DLY_8);
	buzzer_sound_note(N_G3,DLY_8);
	buzzer_sound_note(N_C3,DLY_8);
	buzzer_sound_note(N_C3,DLY_8);
	buzzer_sound_note(N_D4,DLY_4);
	buzzer_sound_note(N_A3,DLY_3);
}
