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

void init();
void display_text(char *str);
void set_cursor(int position);