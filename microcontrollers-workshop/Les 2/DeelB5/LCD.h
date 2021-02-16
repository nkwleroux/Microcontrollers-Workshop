/*
 * LCD.h
 *
 * Created: 16/2/2021 12:29:17 PM
 *  Author: Nic
 */ 

#ifndef LCD_H_
#define LCD_H_

void init();
void display_text(char *str);
void set_cursor(int position);

#endif /* LCD_H_ */