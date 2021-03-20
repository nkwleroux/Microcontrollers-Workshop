/*
 * Buzzer.h
 *
 * Created: 20/3/2021 1:27:16 PM
 *  Author: Nic
 */ 

#ifndef Buzzer_H_
#define Buzzer_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include <math.h>

#define ON 1
#define OFF 0

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
#define B1_		1043		
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
#define B2 		B1*2
#define B2_ 	B1_*2	

#define DLY_1	DLY_4*4	
#define DLY_2	DLY_4*2	
#define DLY_4 	800		
#define DLY_8	DLY_4/2	
#define DLY_16	DLY_4/4	

static volatile long T1HIGHCNT = 0xFD, T1LOWCNT = 0X66;
static volatile int SoundState = ON;
static volatile int Soundonoff = ON;

ISR(TIMER1_OVF_vect);

void buzzer_init(void);

void buzzer_sound(int freq);
void buzzer_no_sound(void);

void buzzer_sound_Note(int tone, int dly);
void buzzer_test_sounds(void);

#endif /* Buzzer_H_ */