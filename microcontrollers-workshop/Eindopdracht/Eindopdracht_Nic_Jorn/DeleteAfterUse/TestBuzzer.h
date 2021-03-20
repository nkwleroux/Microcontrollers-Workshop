/*
 * TestBuzzer.h
 *
 * Created: 20/3/2021 1:27:16 PM
 *  Author: Nic
 */ 


#ifndef TESTBUZZER_H_
#define TESTBUZZER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include <math.h>

#define ON 1
#define OFF 0

#define MaxLine 2
#define MaxCol 16
//
#define DELAYTIME	1
#define DELAYTIME1	0

static volatile long T1HIGHCNT = 0xFD, T1LOWCNT = 0X66;
static volatile int SoundState = ON;
static volatile int Soundonoff = ON;

#define C1		523		
#define C1_		554
#define D1		587		
#define D1_		622
#define E1		659		
#define F1		699		
#define F1_		740
#define G1		784		
#define G1_		831
#define A1		880		
#define A1_		932
#define B1		988		
#define C2		C1*2	
#define C2_		C1_*2
#define D2		D1*2	
#define D2_		D1_*2
#define E2		E1*2	
#define F2		F1*2	
#define F2_		F1_*2
#define G2		G1*2	
#define G2_ 	G1_*2
#define A2		A2*2	
#define A2_		A2_*2
#define B2 		B2*2	

#define DLY_1	DLY_4*4	
#define DLY_2	DLY_4*2	
#define DLY_4 	800		
#define DLY_8	DLY_4/2	
#define DLY_16	DLY_8/2	

// public function
extern void timer1_init(void);
extern void soundNote(int tone, int dly);
extern void SoundNotice(void);
extern void pong(void);

// private function
ISR(TIMER1_OVF_vect);
void wait_ms(int timer_ms);
void sound(int freq);
void nosound(void);

#endif /* TESTBUZZER_H_ */