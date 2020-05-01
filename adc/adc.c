#include "main.h"

#define TSADCCON0	0xE1700000
#define TSDATX0		0xE170000C
#define TSDATY0		0xE1700010
#define CLRINTADC0	0xE1700018
#define ADCMUX		0xE170001C


#define rTSADCCON0	(*(volatile unsigned int *)TSADCCON0)
#define rTSDATX0	(*(volatile unsigned int *)TSDATX0)
#define rTSDATY0	(*(volatile unsigned int *)TSDATY0)
#define rCLRINTADC0	(*(volatile unsigned int *)CLRINTADC0)
#define rADCMUX		(*(volatile unsigned int *)ADCMUX)

void start_convert(void)
{
	rTSADCCON0 |= (1<<0);
}

void adc_init(void)
{
	rTSADCCON0 |= (1<<16);
	rTSADCCON0 |= (1<<14);
	rTSADCCON0 &= ~(0xFF<<6);
	rTSADCCON0 |= (65<<6);
	rTSADCCON0 &= ~(1<<2);
	rTSADCCON0 &= ~(1<<1);
	rADCMUX &= ~(0xf);
}

int convert_complete(void)
{
	while(!(rTSADCCON0 & (1<<15)));
	return 1;
}

int read_xvalue(void)
{
	if (convert_complete()) {
		return (rTSDATX0 & 0xfff);
	}
}

int read_yvalue(void)
{
	if (convert_complete()) {
		return (rTSDATY0 & 0xfff);
	}
}

void print_adc_value(void)
{
	int x, y;
	while (1) {
		start_convert();
		x = read_xvalue();
		y = read_yvalue();
		printf("X 值：%d, Y 值：%d\n", x, y);
		delay();
	}
}