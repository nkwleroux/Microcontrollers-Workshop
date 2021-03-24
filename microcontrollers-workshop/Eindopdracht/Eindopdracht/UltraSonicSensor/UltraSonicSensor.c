/*
 * UltraSonicSensor.c
 *
 * Created: 20/3/2021 3:03:33 PM
 *  Author: Nic & Jorn
 */ 

#define F_CPU 8e6

#include "Include/UltraSonicSensor.h"

enum interrupt_status {INTERRUPT_FALLING, INTERRUPT_RISING};

static volatile enum interrupt_status int_stat = INTERRUPT_RISING;

uint16_t timer_dist = 125; // time measured by timer;

volatile int i = 0;

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

void interrupt0_init(void){
	EICRA = 0x0c; //INIT1 rising edge. 
	EIMSK = 0x02; //Enable INT1.
}

void ussensor_init(void){
	interrupt0_init();
	DDRD = 0x01; // pulse
	TCCR1A = 0b00000000; 
	TCCR1B = 0b00001100; // CTC compare A, RUN
}

void ussensor_pulse_signal(void){
	PORTD = 0x01; //sends a high signal
	wait_us(10); //duration of the pulse in microseconds(us)
	PORTD = 0x00; //sends a low signal	
}

ISR(INT1_vect)
{
	// if the interrupt was generated on a rising edge (start sending echo)
	if (int_stat == INTERRUPT_RISING)
	{
		// set interrupt pin 0 on PORTD to falling edge
		EICRA = 0b00001000; //0x08
		//EICRA = 0b00001100;
		
		// reset the time in timer1
		TCNT1 = 0x00;
		
		// set interrupt status
		int_stat = INTERRUPT_FALLING;
	} else
	// else if it was generated on a falling edge (end sending echo)
	{
		// set interrupt pin 0 on PORTD to rising edge
		EICRA = 0b00001100; //0x0c
		//EICRA = 0b00001000;
		
		// read timer1 into time_dist
		timer_dist = TCNT1;
		
		// set interrupt status
		int_stat = INTERRUPT_RISING;
	}
}

int calculate_distance(void){
		/*return timer_dist /58;*/
	return timer_dist * (340 / 2) / 58 / 5;
}

int get_i(){
	return i;
}

