/*
 * LCD.h
 *
 * Created: 17/3/2021 9:18:09 AM
 *  Author: Nic
 */ 

#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void init_lcd(void);
void lcd_strobe_lcd_e(void);
void lcd_write_data(unsigned char byte );
void lcd_write_command(unsigned char byte);
void lcd_clear();
void display_text(char *str);
void set_cursor(int position);

#endif