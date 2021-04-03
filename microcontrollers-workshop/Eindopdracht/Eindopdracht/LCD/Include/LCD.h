/*
 * LCD.h
 *
 * Created: 17/3/2021 9:18:09 AM
 *  Author: Nic & Jorn
 */ 

#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void lcd_init(void);
void lcd_clear(void);
void lcd_display_text(char *str);
void lcd_set_cursor(int position);

#endif /* LCD_H_ */