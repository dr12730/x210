#include "stdio.h"

#ifndef MY_MAIN_H
#define MY_MAIN_H

void led_blink(void);

void delay(void);
unsigned char getc(void);
void uart_init(void);

void lcd_init(void);
void lcd_test(void);

#endif
