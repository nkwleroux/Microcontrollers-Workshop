/*
 * LCD.c
 *
 * Created: 16/2/2021 12:29:09 PM
 *  Author: Nic
 */ 
#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LCD.h"

#define LCD_E 3

void init();
void display_text(char *str);
void set_cursor(int position);
void wait( int ms );
void test_hello_world();
void lcd_ledge_e(void);
void lcd_display(char byte, int rs);
void lcd_set_cursor_position_1_left();
void lcd_set_cursor_position_1_right();
void lcd_return_home();
void lcd_write_charCMD(char cmd);
void lcd_write_char(char message);
void lcd_write_line1(char text[]);
void lcd_write_line2(char text[]);
void lcd_reset();
void lcd_clear_screen();
void lcd_set_cursor_left_to_right();
void lcd_set_cursor_blinking_block();
void lcd_switch_power();

void init(){

	DDRC = 0xFF;
	PORTC = 0x00;
	
	lcd_reset();
	lcd_clear_screen();
	lcd_set_cursor_left_to_right();
	lcd_set_cursor_blinking_block();
}

//START init functions

//used to reset the lcd - 4bit interface, 2 lines, 5*7 pixels
void lcd_reset(){
	for(int i = 0;i < 3; i++){
		lcd_write_charCMD(0x28);
		wait(20);
	}
}

void lcd_clear_screen(){
	lcd_write_charCMD(0x01);
}

//lcd command 6 in hex
void lcd_set_cursor_left_to_right(){
	lcd_write_charCMD(0x06);
}

//turns on visible blinking block
void lcd_set_cursor_blinking_block(){
	lcd_write_charCMD(0x0F);
}

//END init functions

void test_hello_world(){
	init();
	display_text("hello");
	set_cursor(10);
	display_text("world");
}

void lcd_ledge_e(void) {
	PORTC |= (1<<LCD_E);	// E high
	wait(1);			// nodig
	PORTC &= ~(1<<LCD_E);  	// E low
	wait(1);			// nodig?
}

//START methods used to display text.

void lcd_write_charCMD(char cmd){
	lcd_display(cmd, 0);
}

void lcd_write_char(char message){
	lcd_display(message, 1);
}

void lcd_display(char byte, int rs){
	if(rs){
		rs = 1;
	}
	
	// First nibble.
	PORTC = (byte & 0xF0);
	PORTC |= (rs<<2);
	lcd_ledge_e();

	// Second nibble
	PORTC = (byte & 0xF0) << 4;
	PORTC |= (rs<<2);
	lcd_ledge_e();
}

//not sure if needed
void lcd_write_line1(char text[]){
	lcd_write_charCMD(0x80); //row 1
	for (int i = 0; i <16; i++)
	{
		lcd_write_char(text[i]);
	}
}

//not sure if needed
void lcd_write_line2(char text[]){
	lcd_write_charCMD(0xC0); //row 2
	for (int i = 0; i <16; i++)
	{
		lcd_write_char(text[i]);
	}
}

//END methods for text.

void display_text(char *str){
	for (; *str; str++)
	{
		lcd_write_char(*str);
	}
}
	
void set_cursor(int position){
	lcd_return_home();
	for (int i = 0; i < position; i++)
	{
		lcd_set_cursor_position_1_right();
	}
}

void lcd_set_cursor_position_1_left(){
	lcd_write_charCMD(0x10);
}

void lcd_set_cursor_position_1_right(){
	lcd_write_charCMD(0x14);
}

void lcd_return_home(){
	lcd_write_charCMD(0x02); //used to return home
}

void lcd_switch_power(){
	lcd_write_charCMD(0x00);
}

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

