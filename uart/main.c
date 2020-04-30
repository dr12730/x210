#include "main.h"


#define VIC0_BASE				(0xF2000000)
#define VIC0VECTADDR			(*(volatile T_FUNC *)(VIC0_BASE + 0x100))

int main(void)
{
	int i;

    uart_init();
    printf("\r\n\r\n");
    printf("****************************\n\r");

    for (i = 0; i < 32; i++) {
    	printf("VIC0VECTADDR[%d]: %p\r\n", i, VIC0VECTADDR);
    }

    while(1) {
    	delay();
    }

    return 0;
}
