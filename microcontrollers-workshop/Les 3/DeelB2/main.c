/*
 * DeelB2.c
 *
 * Created: 24/2/2021 10:20:14 AM
 * Author : Nic & Jorn
 */ 
#define F_CPU 8e6

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#define LCD_E 3

volatile int tenthValue = 0; 
volatile int timerPreset = -1;

void lcd_ledge_e(void);
void wait( int ms );
void init_timer(void);
void init_LCD(void);
void lcd_clear_screen(void);
void display(char byte, int rs);
void lcd_write_charCMD(char byte);
void lcd_write_char(char byte);
void display_text(char *str);
void set_cursor(int position);
void lcd_set_cursor_position_1_right(void);
void lcd_scroll_cursor(int position);
void lcd_scroll_display_position_1_right(void);
void lcd_return_home(void);

ISR( TIMER2_COMP_vect );

void lcd_ledge_e(void) {
	PORTC |= (1<<LCD_E);	// E high
	wait(1);			// nodig
	PORTC &= ~(1<<LCD_E);  	// E low
	wait(1);			// nodig?
}

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void init_timer(void){
	TCNT2 = timerPreset;			// Compare value of counter 2
	TIMSK |= 0b01000000;			// T2 compare match interrupt enable BIT(7) or 0x80 = 0b10000000 
	sei();					// turn_on intr all
	TCCR2 = 0x07;		// Initialize T2: timer, prescaler=32, compare output disconnected,CTC,RUN
}

void init_LCD(void){
	DDRC = 0xFF;
	PORTC = 0x00;
	
	PORTC = 0x20;	//Function set (sets to 4 bit mode)
	lcd_ledge_e();

	//1 instruction - Function set (0010 1000)
 	PORTC = 0x20;   //high nibble (0010) DL = 0 (4 bits)
	lcd_ledge_e();
	PORTC = 0x80;	//low nibble (1000) N = 1 (2 lines)
	lcd_ledge_e();
	
	//2 instruction
	PORTC = 0x00;   //Display on/off control
	lcd_ledge_e();
	PORTC = 0xF0;   //Turn on cursor
	lcd_ledge_e();

	//3 instruction
	PORTC = 0x00;   //Entry mode set
	lcd_ledge_e();
	PORTC = 0x60;	//Set CGRAM address to 32
	lcd_ledge_e();
	
	lcd_clear_screen();
}

void lcd_clear_screen(void){
	lcd_write_charCMD(0x01);
	set_cursor(0);
}

void display(char byte, int rs){
	// First nibble.
	PORTC = byte;
	PORTC |= (rs<<2);
	lcd_ledge_e();

	// Second nibble
	PORTC = (byte << 4);
	PORTC |= (rs<<2);
	lcd_ledge_e();
}

void lcd_write_charCMD(char byte){
	display(byte,0);
}

void lcd_write_char(char byte){
	display(byte,1);
}

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
		wait(1);
	}
}

void lcd_set_cursor_position_in_row_2(int postion){
	int pos = 0xc0 + postion;
	lcd_write_charCMD(pos);
}

void lcd_set_cursor_position_1_right(void){
	lcd_write_charCMD(0x14);
}


void lcd_scroll_cursor(int position){
	lcd_return_home();
	for (int i = 0; i < position; i++)
	{
		lcd_scroll_display_position_1_right();
		wait(1);
	}
}

void lcd_scroll_display_position_1_right(void){
	lcd_write_charCMD(0x1E);
}

void lcd_return_home(void){
	lcd_write_charCMD(0x02); //used to return home
	wait(5);
}

ISR( TIMER2_OVF_vect  ) {
	TCNT2 = timerPreset;			// Preset value
	tenthValue++;		// Increment counter
	
	lcd_clear_screen();
	
	char str[10];
	sprintf(str, "%d", tenthValue);
	display_text(str);
	wait(1);
}

int main(void)
{
	init_LCD();
	DDRD = 0x00;
	DDRA = 0xff;
	DDRB = 0xff;
	init_timer();

    while (1) 
    {
		PORTA = TCNT2;
		PORTB = tenthValue;
    }
}

