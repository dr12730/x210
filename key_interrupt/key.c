#include "main.h"

// 定义操作寄存器的宏
#define GPH0CON		0xE0200C00
#define GPH0DAT		0xE0200C04
#define GPH2CON		0xE0200C40
#define GPH2DAT		0xE0200C44

#define rGPH0CON	(*(volatile unsigned int *)GPH0CON)
#define rGPH0DAT	(*(volatile unsigned int *)GPH0DAT)
#define rGPH2CON	(*(volatile unsigned int *)GPH2CON)
#define rGPH2DAT	(*(volatile unsigned int *)GPH2DAT)

#define EXT_INT_0_CON	0xE0200E00
#define EXT_INT_2_CON	0xE0200E08
#define EXT_INT_0_PEND	0xE0200F40
#define EXT_INT_2_PEND	0xE0200F48
#define EXT_INT_0_MASK	0xE0200F00
#define EXT_INT_2_MASK	0xE0200F08

#define rEXT_INT_0_CON	(*(volatile unsigned int *)EXT_INT_0_CON)
#define rEXT_INT_2_CON	(*(volatile unsigned int *)EXT_INT_2_CON)
#define rEXT_INT_0_PEND	(*(volatile unsigned int *)EXT_INT_0_PEND)
#define rEXT_INT_2_PEND	(*(volatile unsigned int *)EXT_INT_2_PEND)
#define rEXT_INT_0_MASK	(*(volatile unsigned int *)EXT_INT_0_MASK)
#define rEXT_INT_2_MASK	(*(volatile unsigned int *)EXT_INT_2_MASK)

// GPH0[2:3], GPH2[0:3]

void key_exint_init(void)
{
	// 将按键设置为外部中断 
	rGPH0CON |= 0xFF << 8;
	rGPH2CON |= 0xFFFF;

	// 设置为上升沿触发
	rEXT_INT_0_CON &= ~(0xFF<<8);
	rEXT_INT_0_CON = 0x33<<8;
	rEXT_INT_2_CON &= ~(0xFFFF);
	rEXT_INT_2_CON = 0x3333;

	// 打开中断
	rEXT_INT_0_MASK &= ~(3<<2);
	rEXT_INT_2_MASK &= ~(0xF);

	// 清除中断悬挂
	rEXT_INT_0_PEND |= (3<<2);
	rEXT_INT_2_PEND |= (0x0F<<0);
}

void eint2_key(void)
{
	printf("[左]\r\n");

	rEXT_INT_0_PEND |= (1<<2);
	intc_clearvectaddr();
}


void eint3_key(void)
{
	printf("[下]\r\n");

	rEXT_INT_0_PEND |= (1<<3);
	intc_clearvectaddr();
}


void eint1619_key(void)
{

	if (rEXT_INT_2_PEND & (1<<0)) {
		printf("[上]\r\n");
	} else if (rEXT_INT_2_PEND & (1<<1)) {
		printf("[右]\r\n");
	} else if (rEXT_INT_2_PEND & (1<<2)) {
		printf("[回退]\r\n");
	} else if (rEXT_INT_2_PEND & (1<<3)) {
		printf("[菜单]\r\n");
        }

	rEXT_INT_2_PEND |= (0x0f<<0);
	intc_clearvectaddr();
}
