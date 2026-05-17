
#include <stdint.h>
#include "stm32f0xx.h"
#include <stdio.h>
#include "systick.h"
#include "led.h"

int main(void)
{

	ledInit();
    while (1)
    {
    		GPIOA->BSRR |= (1U << 5);
    		delay_systick(1000);
    		GPIOA->BSRR |= (1U<<21);
    		delay_systick(3000);

    }
}
