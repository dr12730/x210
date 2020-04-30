#include "main.h"

void reset_exception(void)
{
	printf("reset_exception 处理函数\n");
}

void undef_exception(void)
{
	printf("undef_exception 处理函数\n");
}

void soft_exception(void)
{
	printf("soft_exception 处理函数\n");
}
void prefetch_exception(void)
{
	printf("prefetch_exception 处理函数\n");
}

void data_exception(void)
{
	printf("data_exception 处理函数\n");
}

void system_init_exception(void)
{
	r_exception_reset	 = (T_FUNC)&reset_exception;
	r_exception_undef = (T_FUNC)&undef_exception;
	r_exception_sotf_int = (T_FUNC)&soft_exception;
	r_exception_prefetch = (T_FUNC)&prefetch_exception;
	r_exception_data = (T_FUNC)&data_exception;
	r_exception_irq = (T_FUNC)&IRQ_handle;
	r_exception_fiq = (T_FUNC)&IRQ_handle;
}

void intc_init(void)
{
	// 由中断控制器禁用所有中断
   	VIC0INTENCLEAR = 0xffffffff;
    VIC1INTENCLEAR = 0xffffffff;
    VIC2INTENCLEAR = 0xffffffff;
    VIC3INTENCLEAR = 0xffffffff;
	// 设置为 IQR 中断模式
	VIC0INTSELECT = 0x0;
	VIC1INTSELECT = 0x0;
	VIC2INTSELECT = 0x0;
	VIC3INTSELECT = 0x0;

	//清除中断向量地址
	intc_clearvectaddr();

}

void intc_clearvectaddr(void)
{
	VIC0ADDR = 0x0;
	VIC1ADDR = 0x0;
	VIC2ADDR = 0x0;
	VIC3ADDR = 0x0;
}

void intc_enable(unsigned long intnum)
{
	if (intnum < 32) {
		VIC0INTENABLE |= (1 << intnum);
	} else if (intnum < 64) {
		VIC1INTENABLE |= (1 << (intnum-32));
	} else if (intnum < 96) {
		VIC2INTENABLE |= (1 << (intnum-64));
	} else if (intnum < 200) {
		VIC3INTENABLE |= (1 << (intnum-96));
	}
}

void intc_disable(unsigned long intnum)
{
	if (intnum < 32) {
		VIC0INTENCLEAR |= (1 << intnum);
	} else if (intnum < 64) {
		VIC1INTENCLEAR |= (1 << (intnum-32));
	} else if (intnum < 96) {
		VIC2INTENCLEAR |= (1 << (intnum-64));
	} else if (intnum < 200) {
		VIC3INTENCLEAR |= (1 << (intnum-96));
	}
}

void intc_setvectaddr(unsigned long intnum, T_FUNC handler)
{
	T_FUNC *base[4] = {(T_FUNC*)&VIC0VECTADDR, 
						(T_FUNC *)&VIC1VECTADDR, 
						(T_FUNC *)&VIC2VECTADDR, 
						(T_FUNC *)&VIC3VECTADDR};
	int num = 0;
	if (intnum < 32) {
		num = 0;
	} else if (intnum < 64) {
		num = 1;
		intnum -= 32;
	} else if (intnum < 96) {
		num = 2;
		intnum -= 64;
	} else if (intnum < 200) {
		num = 3;
		intnum -= 96;
	}
	base[num][intnum] = handler;
}

unsigned long intc_getvicirqstatus(unsigned long ucontroller)
{
	switch (ucontroller) {
	case 0: return VIC0IRQSTATUS; break;
	case 1: return VIC1IRQSTATUS; break;
	case 2: return VIC2IRQSTATUS; break;
	case 3: return VIC3IRQSTATUS; break;
	default: return 0;
	}
}

void irq_handler(void)
{
	int i;
	T_FUNC *vicAddr[4] = {
				(T_FUNC *)&VIC0ADDR, 
				(T_FUNC *)&VIC1ADDR, 
				(T_FUNC *)&VIC2ADDR, 
				(T_FUNC *)&VIC3ADDR};
	T_FUNC *isr = NULL;

	for (i = 0; i < 4; i++) {
		if (intc_getvicirqstatus(i)) {
			isr = vicAddr[i];
			break;
		}
	}

	(*isr)();
}