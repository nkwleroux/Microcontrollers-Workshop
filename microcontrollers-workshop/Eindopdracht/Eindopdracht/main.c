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

#define MinDistance 800
#define CollisionTone F1_

static void wait_ms(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void init_components(void){
	lcd_init();
	wait_ms(100);
	init_Buzzer();
	wait_ms(100);
	ussensor_init();
	wait_ms(100);
	sei();
}

void calculate_and_dislpay_distance(char *distanceText){
	lcd_clear();
	int distance = calculate_distance();
	sprintf(distanceText,"%d cm",distance);
	lcd_display_text(distanceText);
};

void display_frequency(char *distanceText, int tone){
	lcd_set_cursor(40);
	int distance = frequency_distance();
	//distance += 3000; //frequency is off by + 3000 +- 200. (between 2800 and 3200)
	sprintf(distanceText,"%d hz",distance);
	lcd_display_text(distanceText);
}

//Used in conjunction with Buzzer, LCD, Ultrasonic sensor
void sound_collision_detection(int tone){
	int distance = frequency_distance();
	if(distance > MinDistance){
		if(distance > 2200){
			soundNote(tone,DLY_16/2);
		}
		if(distance > 2100){
			soundNote(tone,DLY_16);
		}else if(distance > 2000){
			soundNote(tone,DLY_8);
		}else if(distance > 1800){
			soundNote(tone,DLY_4);
		}
	}
}

int oldDistance = 1600;

void sound_distance_in_hz_with_step(){
	int distance = frequency_distance();
	int distanceDifference;
	int step = 10;
	
	if(distance > oldDistance){
		//distanceDifference = distance - oldDistance;
		//step = distanceDifference / 10;
		while(distance > oldDistance){
			oldDistance+=step;
			sound(oldDistance);
			wait_ms(10);
		}
	}else if (distance < oldDistance){
		//distanceDifference = oldDistance - distance;
		//step = distanceDifference / 10;
		while(distance < oldDistance){
			oldDistance-=step;
			sound(oldDistance);
			wait_ms(10);
		}
	}
	
	oldDistance = distance;
}

void sound_distance_in_hz(){
	int distance = frequency_distance();
	if(distance > MinDistance){
		sound(distance);
	}
}

void display_timer_distance(char *distanceText){
	//timer distance (debug only)
	lcd_set_cursor(40);
	int distance = get_timer_dist();
	sprintf(distanceText,"%d timer",distance);
	lcd_display_text(distanceText);
}

void display_int_text(int cursor, int num, char *distanceText){
	lcd_set_cursor(cursor);
	sprintf(distanceText,"mode %d",num);
	lcd_display_text(distanceText);
}

//Don't use DDRA & DDRC because the LCD uses it.
int main(void){
	
	init_components();
	
	nosound();
	
	char distanceText[16];
	
	DDRG = 0x00;
	DDRF = 0xFF;
	PORTF = 0x00;
	int buttonPress = 0;
	
    while (1) 
    {
		//start code for sensor
		
		ussensor_pulse_signal();
		
		//end code for sensor

// 		start code for buzzer
		if(PING & 0x01){
			PORTF ^= 0xFF;
			//buttonPress++;
			wait_ms(50);
		}
		
		if(PING & 0x02){
			buttonPress++;
			if(buttonPress >= 3){
				buttonPress = 0;
			}
			wait_ms(50);
		}
		if(PING & 0x04){
			lcd_clear();
			lcd_display_text("playing song");
			test_sounds();
			lcd_clear();
			lcd_display_text("finished song");
			wait_ms(500);
		}
		
		//start code for lcd
		
		calculate_and_dislpay_distance(distanceText);
		//display_frequency(distanceText,CollisionTone);
		display_int_text(40,buttonPress,distanceText);
		
		
		//debug
		// 		int distance = get_timer_dist();
		// 		debug_int_text(40,distance,distanceText);
		//debug_int_text(40,buttonPress, distanceText);


		//end code for lcd
		
		if(PORTF == 0xFF){
			nosound();	
		}
		
		if(PORTF == 0x00){ 
			if(buttonPress % 3 == 0){
				sound_collision_detection(CollisionTone);
			}
			if(buttonPress % 3 == 1){
				sound_distance_in_hz();
			}
			if(buttonPress % 3 == 2){
				sound_distance_in_hz_with_step();
			}
		}
		
		//end code for buzzer
		
		wait_ms(60);	//Duration of the time in between the pulses in miliseconds(ms)
			//wait_ms(1000);			//Needed for the ussensor.
		
	}
}


