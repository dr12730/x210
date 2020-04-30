#include "main.h"

// #define WDT_INT   // 看门狗中断开关
// #define WDT_RESET   // 看门狗复位开关
// #define PWM_TIMER   // PWM定时器开关

int main(void)
{
	int i;

    uart_init();
    printf("\r\n\r\n");
    printf("*************************\r\n");

    // 中断控制器初始化
    intc_init();
    // 中断向量表初始化
    system_init_exception();
    // GPIO外部中断初始化
    key_exint_init();

    // 将 eint2_key 和 eint2 中断号绑定
    intc_setvectaddr(NUM_EINT2, &eint2_key);
    intc_setvectaddr(NUM_EINT3, &eint3_key);
    intc_setvectaddr(NUM_EINT16_31, &eint1619_key);
    
    // 打开中断响应
    intc_enable(NUM_EINT2);
    intc_enable(NUM_EINT3);
    intc_enable(NUM_EINT16_31);


#ifdef PWM_TIMER
    // 定时器2 pwm 初始化
    timer2_pwm_init();
    // 绑定 timer2 中断和中断处理函数
    intc_setvectaddr(NUM_TIMER2, &timer2_interrupt);
    // 打开timer2中断响应
    intc_enable(NUM_TIMER2);
#endif

#ifdef WDT_INT && !WDT_RESET
    // 看门狗中断初始化 
    init_wdt_interrupt();
    // 绑定看门狗中断处理函数
    intc_setvectaddr(NUM_WDT, wdt_print);
    intc_enable(NUM_WDT);
#endif

#ifdef WDT_RESET && !WDT_INT
    // 看门狗中断初始化 
    init_wdt_reset();
    // 绑定看门狗中断处理函数
    intc_setvectaddr(NUM_WDT, wdt_print);
    intc_enable(NUM_WDT);
#endif

    // 读写RTC：将 RTC 设置为 2020.4.18 13:27:32
    write_rt();
    rtc_interrupt_init();
    intc_setvectaddr(NUM_RTC_ALARM, rtc_interrupt);
    intc_enable(NUM_RTC_ALARM);

    while(1) {
    	delay();
    }

    return 0;
}
