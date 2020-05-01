#include "main.h"

int main(void)
{

    uart_init();
    adc_init();
    printf("\n\n");
    printf("****************************\n");

    print_adc_value(); 


    
    while(1) {
    	delay();
    }

    return 0;
}
