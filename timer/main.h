#include "stdio.h"
#include "intc.h"

#ifndef MY_MAIN_H
#define MY_MAIN_H

void led_blink(void);

void delay(void);
unsigned char getc(void);
void uart_init(void);

// 中断控制器
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

// 按键中断
void key_exint_init(void);
void eint2_key(void);
void eint3_key(void);
void eint1619_key(void);

// 定时器
void timer2_pwm_init(void);
void timer2_interrupt(void);
// 看门狗
void init_wdt_interrupt(void);
void wdt_print(void);
void init_wdt_reset(void);
// RTC 闹钟
void rtc_interrupt_init(void);
void rtc_interrupt(void);
#endif