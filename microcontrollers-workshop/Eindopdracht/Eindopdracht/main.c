/*
 * main.c
 *
 * Created: 17/3/2021 9:16:11 AM
 * Author : Nic & Jorn
 */ 

#define F_CPU 8e6

#include "Buzzer/Include/Buzzer.h"
#include "LCD/Include/LCD.h"
#include "UltraSonicSensor/Include/UltraSonicSensor.h"
#include <stdio.h>

#define MinDistance 800
#define CollisionTone N_FS5

static volatile int oldDistance = 0;

static void wait_ms(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

//Method used to initialize the components.
void init_components(void){
	lcd_init();
	wait_ms(100);
	buzzer_init();
	wait_ms(100);
	ussensor_init();
	wait_ms(100);
	sei();
}

//Method used to display the distance in cm.
void dislpay_distance_in_cm(char *distanceText){
	lcd_clear();
	int distance = calculate_distance();
	sprintf(distanceText,"%d cm",distance);
	lcd_display_text(distanceText);
};

//Method used to display the current mode of the buzzer/usssensor
void display_mode(int cursor, int num, char *distanceText){
	lcd_set_cursor(cursor);
	sprintf(distanceText,"mode %d",num);
	lcd_display_text(distanceText);
}

//Frequency is off by + 3000 +- 200. (between 2800 and 3200)
//Method is not used.
void display_frequency(char *distanceText, int tone){
	lcd_set_cursor(40);
	int distance = frequency_distance();
	//distance += 3000; 
	sprintf(distanceText,"%d hz",distance);
	lcd_display_text(distanceText);
}

//Used in conjunction with Buzzer, LCD, ultrasonic sensor
void sound_collision_detection(int tone){
	int distance = frequency_distance();
	if(distance > MinDistance){
		if(distance > 2200){
			buzzer_sound_note(tone,DLY_16/4);
		}else if(distance > 2100){
			buzzer_sound_note(tone,DLY_16/2);
		}else if(distance > 2000){
			buzzer_sound_note(tone,DLY_16);
		}else if(distance > 1900){
			buzzer_sound_note(tone,DLY_8);
		}else if(distance > 1800){
			buzzer_sound_note(tone,DLY_4);
		}
	}
}

//Method used to output a sound with the buzzer in
// correlation to the distance measured by the usssensor.
//This method has no delay and changes frequency immediately
// with no fluid transition.
void sound_distance_in_hz(void){
	int distance = frequency_distance();
	if(distance > MinDistance){
		buzzer_sound(distance);
	}
}

//Method used to output a sound with the buzzer in
// correlation to the distance measured by the usssensor.
//This method has delay which in turn makes the frequency in accurate
// depending on where the users hand is.
void sound_distance_in_hz_with_step(void){
	int distance = frequency_distance();
	int step = 10;
	
	if (oldDistance == 0)
	{
		buzzer_sound(distance);
	}else{
		if(distance > oldDistance){
			while(distance > oldDistance){
				oldDistance+=step;
				buzzer_sound(oldDistance);
				wait_ms(10);
			}
		}else if (distance < oldDistance){
			while(distance < oldDistance){
				oldDistance-=step;
				buzzer_sound(oldDistance);
				wait_ms(10);
			}
		}
	}
	
	oldDistance = distance;
}

int main(void){
	
	init_components();
	
	buzzer_sound_off();
	
	char distanceText[16];
	
	DDRG = 0x00;
	DDRF = 0xFF;
	PORTF = 0x00;
	int buttonPress = 0;
	
    while (1) 
    {
		
		//Pulse a signal to the ultrasonic sensor
		ussensor_pulse_signal();

		//If button PG0 is pressed, then flip the bits on PORTF.
		if(PING & 0x01){
			PORTF ^= 0xFF;
			wait_ms(50);
		}
		
		//If button PG1 is pressed, then this will change the mode of the ultrasonic sensor and buzzer.
		if(PING & 0x02){
			buttonPress++;
			if(buttonPress >= 3){
				buttonPress = 0;
			}
			wait_ms(50);
		}
		
		//If button PG2 is pressed, then a short song will play.
		if(PING & 0x04){
			lcd_clear();
			lcd_display_text("playing song");
			buzzer_play_song();
			lcd_clear();
			lcd_display_text("finished song");
			wait_ms(500);
		}
		
		//Methods used to display the distance in cm and mode of the usssensor/buzzer
		dislpay_distance_in_cm(distanceText);
		display_mode(40,buttonPress,distanceText);
		
		//Checks if the bits on PORTF are set. 
		//If true then it turns of the sound of the buzzer.
		if(PORTF == 0xFF){
			buzzer_sound_off();	
		}
		
		//If the bits are off on PORTF then goes through the if statements.
		//Changes the buzzer mode
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
		
		//Duration of the time in between the pulses in miliseconds(ms).
		//Cant be shorter than 60ms. It is needed for the ussensor.
		wait_ms(60);	
		
	}
}


