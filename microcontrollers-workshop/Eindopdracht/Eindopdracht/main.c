/*
 * main.c
 *
 * Created: 17/3/2021 9:16:11 AM
 * Author : Nic
 */ 

#define F_CPU 8e6

#include "Buzzer/Include/Buzzer.h"
#include "LCD/Include/LCD.h"
#include "UltraSonicSensor/Include/UltraSonicSensor.h"
#include <stdio.h>

static void wait_ms(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void init_components(void){
	lcd_init();
	wait_ms(100);
	//init_Buzzer();
	wait_ms(100);
	ussensor_init();
	wait_ms(100);
	sei();
}

//Don't use DDRA & DDRC because the LCD uses it.
int main(void)
{
	init_components();
	
	int16_t COUNTA = 0;
	char SHOWA [16];
	
    while (1) 
    {
		//start code for sensor
		
		ussensor_pulse_signal();
		
		//calculate_distance();
		
		//end code for sensor
		
		//start code for buzzer
		
		//test_sounds();

		//end code for buzzer

		//start code for lcd
		
		
		lcd_clear();
		COUNTA = calculate_distance();
		//COUNTA = get_i();
		sprintf(SHOWA,"%d test",COUNTA);
		//itoa(COUNTA,SHOWA,10);
		lcd_display_text(SHOWA);

// 		lcd_clear();
// 		lcd_display_text("Test lcd");

		//end code for lcd
		
		wait_ms(1000);	//Duration of the time in between the pulses in miliseconds(ms)
						//Needed for the ussensor.
	}
}

