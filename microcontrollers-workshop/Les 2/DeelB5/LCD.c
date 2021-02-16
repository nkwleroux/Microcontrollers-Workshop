/*
 * LCD.c
 *
 * Created: 16/2/2021 12:29:09 PM
 *  Author: Nic
 */ 
#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void init(){

	DDRB = 0xFF;
	PORTB = 0x00;
	
	lcd_reset();
	lcd_clear_screen();
	lcd_set_cursor_left_to_right();
	lcd_set_cursor_blinking_block();
	
}

void lcd_display(char bytes, int rs){
	
}

void display_text(char *str);
void set_cursor(int position);

void lcd_set_home(){
	lcd_write_charCMD(0x02); //used to return home
}

void lcd_write_charCMD(char cmd){
	lcd_display(cmd, 1);
}

void lcd_write_char(char message){
	lcd_display(message, 0);
}

void lcd_write_line1(char text[]){
	lcd_write_charCMD(0x80); //row 1
	for (int i = 0; i <16; i++)
	{
		lcd_write_char(text[i]);
	}
}

void lcd_write_line2(char text[]){
	lcd_write_charCMD(0xC0); //row 2
	for (int i = 0; i <16; i++)
	{
		lcd_write_char(text[i]);
	}
}

//used to reset the lcd - 4bit interface, 2 lines, 5*7 pixels
void lcd_reset(){
	for(int i;i < 3; i++){
		lcd_write_charCMD(0x28);
		wait(20);
	}
}

void lcd_clear_screen(){
	lcd_write_charCMD(0x01);	
}

void lcd_set_cursor_left_to_right(){
	lcd_write_charCMD(0x06);
}

void lcd_set_cursor_blinking_block(){
	lcd_write_charCMD(0x0F);
}

