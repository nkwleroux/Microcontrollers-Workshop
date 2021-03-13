/*
 * LCD.h
 *
 * Created: 13/3/2021 11:29:04 AM
 *  Author: Nic & Jorn
 */ 

#ifndef LCD_H_
#define LCD_H_

#define LCD_E 	3

void wait( int ms );
void init_lcd( void );
void lcd_strobe_lcd_e(void);
void lcd_write_data( unsigned char byte );
void lcd_write_command(unsigned char byte);
void lcd_clear();
void display_text(char *str);
void set_cursor( int position );

#endif