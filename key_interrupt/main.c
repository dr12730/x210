#include "main.h"


#define VIC0_BASE				(0xF2000000)
#define VIC0VECTADDR			(*(volatile T_FUNC *)(VIC0_BASE + 0x100))

int main(void)
{
	int i;

    uart_init();
    printf("\r\n\r\n");
    printf("*************************\r\n");
    intc_init();
    system_init_exception();
    key_exint_init();



    intc_setvectaddr(NUM_EINT2, &eint2_key);
    intc_setvectaddr(NUM_EINT3, &eint3_key);
    intc_setvectaddr(NUM_EINT16_31, &eint1619_key);

    intc_enable(NUM_EINT2);
    intc_enable(NUM_EINT3);
    intc_enable(NUM_EINT16_31);


    while(1) {
    	delay();
    }

    return 0;
}
