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

void init_hello_world();

void lcd_ledge_e(void);

void lcd_set_cursor_position_1_left();

void lcd_set_cursor_position_1_right();

void lcd_return_home();

void lcd_write_charCMD(char cmd);

void lcd_write_char(char message);

//used to reset the lcd - 4bit interface, 2 lines, 5*7 pixels
void lcd_reset();

void lcd_clear_screen();

//lcd command 6 in hex
void lcd_set_cursor_left_to_right();

//turns on visible blinking block
void lcd_set_cursor_blinking_block();

void lcd_switch_power();

#endif /* LCD_H_ */