/*
 * UltraSonicSensor.c
 *
 * Created: 20/3/2021 3:03:33 PM
 *  Author: Nic & Jorn
 */ 

#define F_CPU 8e6

#include "Include/UltraSonicSensor.h"

#define SpeedOfSound 340
#define DistanceInCM 58

enum interrupt_status {FALLING_EDGE, RISING_EDGE};

static volatile enum interrupt_status status = RISING_EDGE;

uint16_t timer_dist = 125; // time measured by timer;

static void wait_us(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_us( 1 );		
	}
}

//Initializes interrupt 1
void interrupt1_init(void){
	EICRA = 0x0c; //INIT1 rising edge. 
	EIMSK = 0x02; //Enable INT1.
}

//Initializes all the ultrasonic sensor components.
void ussensor_init(void){
	interrupt1_init();		//
	DDRD = 0x01; 
	TCCR1A = 0b00000000;	//Timer/Counter1 Control Register A 
	TCCR1B = 0b00001100;	//Timer/Counter1 Control Register B CTC compare A
}

//Method used to pulse a signal to the ultrasonic sensor
void ussensor_pulse_signal(void){
	PORTD = 0x01;	//Sends a high signal
	wait_us(10);	//Duration of the pulse in microseconds(us)
	PORTD = 0x00;	//Sends a low signal	
}

//Interrupt 1, makes use of timer 1
ISR(INT1_vect)
{
	//If the interrupt was generated on a rising edge (Send echo).
	if (status == RISING_EDGE)
	{
		//Set interrupt pin 1 on PORTD to falling edge
		EICRA = 0b00001000; //0x08
		
		//Reset the time in timer1
		TCNT1 = 0x00;
		
		//Set interrupt status
		status = FALLING_EDGE;
	} 
	//If it was generated on a falling edge (End echo).
	else {
		//Set interrupt pin 1 on PORTD to rising edge
		EICRA = 0b00001100; //0x0c
		
		//Read timer1 into time_dist
		timer_dist = TCNT1;
		
		//Set interrupt status
		status = RISING_EDGE;
	}
}

//Calculate distance in cm
int calculate_distance(void){
	return timer_dist * SpeedOfSound / DistanceInCM / 10;
}

//Calculate frequency distance.
int frequency_distance(void){
	return 2500 - (timer_dist * SpeedOfSound / 20);
}



