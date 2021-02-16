/*
 * LCD.h
 *
 * Created: 16/2/2021 12:29:17 PM
 *  Author: Nic
 */ 

#ifndef LCD_H_
#define LCD_H_

//Required
void init();
void display_text(char *str);
void set_cursor(int position);

//Added
void wait( int ms );
void lcd_display(char bytes, int rs);
void lcd_set_home();
void lcd_write_charCMD(char cmd);
void lcd_write_char(char message);
void lcd_write_line1(char text[]);
void lcd_write_line2(char text[]);
void lcd_reset();

#endif /* LCD_H_ */