/*
 * TestBuzzer.c
 *
 * Created: 20/3/2021 1:28:50 PM
 *  Author: Nic
 */ 

#include "TestBuzzer.h"

//////////////////////////////////////////// --------- //////////////////////////////////////////////

ISR(TIMER1_OVF_vect) { //TIMER1 has overflowed
	TCNT1H = T1HIGHCNT;
	TCNT1L = T1LOWCNT;
	if(Soundonoff == ON){
		PORTF = PORTF ^ 0x10;
	}
}

// static void delay_us(unsigned int time_us){
// 	register unsigned int i;
// 	for(i=0; i<time_us; i++){
// 		asm volatile(" PUSH R0 ");
// 		asm volatile(" POP R0 ");
// 		asm volatile(" PUSH R0 ");
// 		asm volatile(" POP R0 ");
// 		asm volatile(" PUSH R0 ");
// 		asm volatile(" POP R0 ");
// 	}
// }

static void wait_us(unsigned int time_us){
	for(unsigned int i=0; i<time_us; i++){
		wait_us(1);
	}
}

// static void delay_ms(unsigned int timer_ms){
// 	unsigned int i;
// 	for(i=0; i<timer_ms; i++){
// 		delay_us(1000);
// 	}
// }

static void wait_ms(unsigned int timer_ms){
	for(unsigned int i=0; i<timer_ms; i++){
		wait_ms(1);
	}
}

///////////////////////////////////////////////////////////
static void sound(int freq){
	Soundonoff = ON;
	T1HIGHCNT = (0xFFFF-floor(1000000/freq)) / 0x100;
	T1LOWCNT = 0xFFFF-floor(1000000/freq) - 0xFF00;
}
static void nosound(void){
	Soundonoff = OFF;
	wait_ms(100);
}
///////////////////////////////////////////////////////////
extern void timer1_init(void) {
	TCCR1B = 0x00;
	//
	TCNT1H = T1HIGHCNT;
	TCNT1L = T1LOWCNT;
	//
	OCR1AH = 0x02;
	OCR1AL = 0x9A;
	//
	OCR1BH = 0x02;
	OCR1BL = 0x9A;
	//
	OCR1CH = 0x02;
	OCR1CL = 0x9A;
	//
	ICR1H = 0x02;
	ICR1L = 0x9A;
	//
	TCCR1A = 0x00;
	TCCR1B = 0x02;
}
///////////////////////////////////////////////////////////
extern void soundNote(int tone, int dly){
	sound(tone);
	wait_ms(dly*2);
	nosound();
}

extern void SoundNotice(void){
	soundNote(C1,DLY_16);
	soundNote(D1,DLY_16);
	soundNote(G1,DLY_16);
}
