/*
 * LCD.c
 *
 * Created: 17/3/2021 9:17:47 AM
 *  Author: Nic & Jorn
 */ 

#define F_CPU 8e6

#include "Include/LCD.h"

static void wait_ms(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void lcd_ledge_e(void) {
	PORTC |= (1<<3);	// E high
	wait_ms(1);
	PORTC &= ~(1<<3);  	// E low
	wait_ms(1);
}

void lcd_init( void ) {
	DDRC = 0xFF;
	PORTC = 0x00;

	PORTC = 0x20;
	lcd_ledge_e();

	PORTC = 0x20;
	lcd_ledge_e();
	
	PORTC = 0x80;
	lcd_ledge_e();

	PORTC = 0x00;
	lcd_ledge_e();
	
	PORTC = 0xF0;
	lcd_ledge_e();

	PORTC = 0x00;
	lcd_ledge_e();
	PORTC = 0x60;
	lcd_ledge_e();
	
	lcd_clear();
	lcd_set_cursor(0);
	
	wait_ms(10);
}

void lcd_write_data(unsigned char byte ) {
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<2);
	lcd_ledge_e();

	// Second nibble
	PORTC = (byte << 4);
	PORTC |= (1<<2);
	lcd_ledge_e();
}

void lcd_write_command(unsigned char byte) {
	// First nibble.
	PORTC = byte;
	PORTC |= (0<<2);
	lcd_ledge_e();

	// Second nibble
	PORTC = (byte << 4);
	PORTC |= (0<<2);
	lcd_ledge_e();
}

void lcd_clear() {
	lcd_write_command(0x01); 
	wait_ms(2);
	lcd_set_cursor(0);
}

void lcd_display_text(char *str) {
	for(;*str; str++){
		lcd_write_data(*str);
	}
}

void lcd_set_cursor( int position ) {
	lcd_write_command(0x80 | position);
}