#include "main.h"

int main(void)
{

    uart_init();
    lcd_init();

    printf("\n\n");
    printf("****************************\n");

    lcd_test();

    while(1) {
    	delay();
    }

    return 0;
}
