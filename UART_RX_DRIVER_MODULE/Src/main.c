
#include <stdint.h>
#include "stm32f0xx.h"
#include <stdio.h>
#include "usart.h"

char datareceived;
int main(void)
{

	uartInit();
	ledInit();
    while (1)
    {
    	datareceived = uartReceive();
    	if (datareceived == '1'){

    		GPIOA->BSRR |= (1U << 5);   // SET

    	}else{
    		GPIOA->BSRR |= (1U<<21);
    	}
    }
}
