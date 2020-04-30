#include "main.h"

#define GPD0CON (0xE02000A0)
#define TCFG0   (0xE2500000)
#define TCFG1   (0xE2500004)
#define TCON    (0xE2500008)
#define TCNTB2  (0xE2500024)
#define TCMPB2  (0xE2500028)
#define TCNTO2  (0xE250002C)
#define TINT_CSTAT  (0xE2500044)
#define WTCON       (0xE2700000)
#define WTDAT       (0xE2700004)
#define WTCNT       (0xE2700008)
#define WTCLRINT    (0xE270000C)

#define rGPD0CON (*(volatile unsigned int *)GPD0CON)
#define rTCFG0   (*(volatile unsigned int *)TCFG0) 
#define rTCFG1   (*(volatile unsigned int *)TCFG1)
#define rTCON    (*(volatile unsigned int *)TCON)
#define rTCNTB2  (*(volatile unsigned int *)TCNTB2)
#define rTCMPB2  (*(volatile unsigned int *)TCMPB2)
#define rTCNTO2  (*(volatile unsigned int *)TCNTO2)
#define rTINT_CSTAT  (*(volatile unsigned int *)TINT_CSTAT)
#define rWTCON       (*(volatile unsigned int *)WTCON)
#define rWTDAT       (*(volatile unsigned int *)WTDAT)
#define rWTCNT       (*(volatile unsigned int *)WTCNT)
#define rWTCLRINT    (*(volatile unsigned int *)WTCLRINT)


#define 	RTC_BASE	 (0xE2800000)
#define		rINTP      	 (*((volatile unsigned int *)(RTC_BASE + 0x30)))
#define		rRTCCON    	 (*((volatile unsigned int *)(RTC_BASE + 0x40)))
#define		rTICCNT    	 (*((volatile unsigned int *)(RTC_BASE + 0x44)))
#define		rRTCALM    	 (*((volatile unsigned int *)(RTC_BASE + 0x50)))
#define		rALMSEC    	 (*((volatile unsigned int *)(RTC_BASE + 0x54)))
#define		rALMMIN    	 (*((volatile unsigned int *)(RTC_BASE + 0x58)))
#define		rALMHOUR  	 (*((volatile unsigned int *)(RTC_BASE + 0x5c)))
#define		rALMDATE     (*((volatile unsigned int *)(RTC_BASE + 0x60)))
#define		rALMMON    	 (*((volatile unsigned int *)(RTC_BASE + 0x64)))
#define		rALMYEAR  	 (*((volatile unsigned int *)(RTC_BASE + 0x68)))
#define		rRTCRST      (*((volatile unsigned int *)(RTC_BASE + 0x6c)))
#define		rBCDSEC    	 (*((volatile unsigned int *)(RTC_BASE + 0x70)))
#define		rBCDMIN   	 (*((volatile unsigned int *)(RTC_BASE + 0x74)))
#define		rBCDHOUR     (*((volatile unsigned int *)(RTC_BASE + 0x78)))
#define		rBCDDATE     (*((volatile unsigned int *)(RTC_BASE + 0x7c))) //DAYWEEK
#define		rBCDDAY      (*((volatile unsigned int *)(RTC_BASE + 0x80)))
#define		rBCDMON      (*((volatile unsigned int *)(RTC_BASE + 0x84)))
#define		rBCDYEAR     (*((volatile unsigned int *)(RTC_BASE + 0x88)))
#define		rCURTICCNT   (*((volatile unsigned int *)(RTC_BASE + 0x90)))
#define		rRTCLVD    	 (*((volatile unsigned int *)(RTC_BASE + 0x94)))



// timer 是 2K Hz 的定时器
// timer_clock = PCLK / ({预分频值 + 1}) / (分频值)
//  = 66000 K / (65+1) / 2 = 500 KHz

int timer_i = 0;
void timer2_pwm_init(void)
{
	// 设置GPD0_2引脚，将其配置为XpwmTOUT_2
	rGPD0CON &= ~(0xf<<8);
	rGPD0CON |= (0x2<<8);
	
	// 设置PWM定时器的一干寄存器，使其工作
	rTCFG0 &= ~(0xff<<8);
	rTCFG0 |= (65<<8);			// prescaler1 = 65, 预分频后频率为1MHz
	
	rTCFG1 &= ~(0x0f<<8);
	rTCFG1 |= (1<<8);			// MUX2设置为1/2,分频后时钟周期为500KHz
	// 时钟设置好，我们的时钟频率是500KHz，对应的时钟周期是2us。也就是说每隔2us
	// 计一次数。如果要定的时间是x，则TCNTB中应该写入x/2us
	
	rTCON |= (1<<15);		// 使能auto-reload，反复定时才能发出PWM波形
	// rTCNTB2 = 250;			// 0.5ms/2us = 500us/2us = 250
	// rTCMPB2 = 125;			// duty = 50%
	
	rTCNTB2 = 8000;			
	rTCMPB2 = 4000;	

	// 每秒
	// rTCNTB2 = 800000;			
	// rTCMPB2 = 400000;	
	
	// 第一次需要手工将TCNTB中的值刷新到TCNT中去，以后就可以auto-reload了
	rTCON |= (1<<13);		// 打开自动刷新功能
	rTCON &= ~(1<<13);		// 关闭自动刷新功能

    rTINT_CSTAT |= (1<<2);	// 打开定时器中断
	
	rTCON |= (1<<12);		// 开timer2定时器。要先把其他都设置好才能开定时器
}


void timer2_interrupt(void)
{
	printf("[%d] 定时器2中断\r\n", timer_i++);
	rTINT_CSTAT |= (1<<7);
	intc_clearvectaddr();
}

// 初始化看门狗，1ms
void init_wdt_interrupt(void)
{
    // 看门狗输入时钟
    // 预分频器 = 65
    rWTCON &= ~(0xFF << 8);
    rWTCON |= (65 << 8);
    // 分频系数 128
    // tClock = 1000K / 128 = 8K
    rWTCON |= (3 << 3);

    // 禁用看门狗复位
	rWTCON |= (1<<2);				// enable wdt interrupt
    rWTCON &= ~(1<<0);

    // 看门狗超时时间，计8k个数是1s
    rWTDAT = 8000;
    rWTCNT = 8000;

    // 启用看门狗
    rWTCON |= (1 << 5);
}

// 看门狗复位
void init_wdt_reset(void)
{
    // 设置预分频值
    // 预分频器 = 65
    rWTCON &= ~(0xFF << 8);
    rWTCON |= (65 << 8);
    // 分频系数 128
    // tClock = 1000K / 128 = 8K
    rWTCON |= (3 << 3);

    // 禁用中断
    rWTCON &= ~(1 << 2);
    // 启用复位
    rWTCON |= (1 << 0);

    // 看门狗超时时间，计8k个数是1s
    rWTDAT = 8000;
    rWTCNT = 8000;

    // 启用看门狗
    rWTCON |= (1 << 5);
}

// 每次看门狗中断打印
void wdt_print(void)
{
    printf("看门狗第[%d]次中断\r\n", ++timer_i);
	rWTCLRINT = 1;
	intc_clearvectaddr();
}

int data2bcd(int data)
{
    return ((data/10)<<4) | ((data%10));
}

int bcd2data(int bcd)
{
    return ((bcd)>>4) * 10 + (bcd&0xf);
}

typedef struct tg_rt {
    unsigned long year;
    unsigned long month;
    unsigned long day;
    unsigned long weekday;
    unsigned long hour;
    unsigned long min;
    unsigned long sec;
} T_RT;

void read_rt(void)
{
    T_RT rt = {
        .year = 0,
        .month = 0,
        .day = 0,
        .weekday = 0,
        .hour = 0,
        .min = 0,
        .sec = 0 
    };

    // 启用 RTC 控制器
    rRTCCON |= 1;

    // 读取 RTC 数据
    rt.year = bcd2data(rBCDYEAR) + 2000;
    rt.month = bcd2data(rBCDMON);
    rt.day = bcd2data(rBCDDAY);
    rt.weekday = bcd2data(rBCDDATE);
    rt.hour = bcd2data(rBCDHOUR);
    rt.min = bcd2data(rBCDMIN);
    rt.sec = bcd2data(rBCDSEC);

    // 关闭 RTC 控制器
    rRTCCON &= ~1;

    printf("当前时间：%d年%d月%d日(%d) %02d:%02d:%02d\r\n", 
        rt.year, rt.month, rt.day, rt.weekday, rt.hour, rt.min, rt.sec);
}

void write_rt(void)
{
    T_RT rt = {
        .year = data2bcd(20),
        .month = data2bcd(4),
        .day = data2bcd(20),
        .weekday = data2bcd(6),
        .hour = data2bcd(13),
        .min = data2bcd(27),
        .sec = data2bcd(32)
    };

    // 启用 RTC 控制器
    rRTCCON |= 1;

    // 写入 RTC 数据
	rBCDSEC     = rt.sec;
	rBCDMIN     = rt.min;
	rBCDHOUR    = rt.hour; 
	rBCDDATE    = rt.weekday; 
	rBCDDAY     = rt.day; 
	rBCDMON     = rt.month; 
	rBCDYEAR    = rt.year; 

    // 关闭 RTC 控制器
    rRTCCON &= ~1;

    read_rt();
}


void rtc_interrupt_init(void)
{
    rALMSEC = data2bcd(35);
    rRTCALM |= 1<<0;
    rRTCALM |= 1<<6;
}

void rtc_interrupt(void)
{
    printf("这是 RTC 闹钟^_^\n\r");
    // 清除中断悬挂位
    rINTP |= (1<<1);
    // 清除中断地址寄存器
    intc_clearvectaddr();   
}