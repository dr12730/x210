#include "stdio.h"
#include "int.h"

#ifndef MY_MAIN_H
#define MY_MAIN_H

void led_blink(void);

void delay(void);
unsigned char getc(void);
void uart_init(void);

void adc_init(void);
void print_adc_value(void);

#endif