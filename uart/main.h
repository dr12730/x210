#include "stdio.h"
#include "int.h"

#ifndef MY_MAIN_H
#define MY_MAIN_H

void led_blink(void);

void delay(void);
unsigned char getc(void);
void uart_init(void);

#if 0
void IRQ_handle(void);
void irq_handler(void);
void intc_setvectaddr(unsigned long intnum, T_FUNC handler);
void intc_disable(unsigned long intnum);
void intc_enable(unsigned long intnum);
void intc_clearvectaddr(void);
void intc_init(void);

void system_init_exception(void);
void reset_exception(void);
void undef_exception(void);
void soft_exception(void);
void prefetch_exception(void);
void data_exception(void);
#endif

#endif