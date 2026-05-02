
#include <stdint.h>

#define RCC_BASE  0x40021000UL //UL means datatype unsigned long
#define GPIOA_BASE 0x48000000UL

#define RCC_AHBENR *(volatile uint32_t *)(RCC_BASE + 0x14) //DEFRENCE POINTER
#define GPIOA_MODER *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE +  0x14)

//simple delay program with loops
void delay(){
	for(volatile int i=0;i<500000; i++){

	}
}
int main()
{
	//Enable clock to GPIOA 17th bit
	RCC_AHBENR |= (1U << 17);
	// 2. Set PA5 as output (clear then set)
	GPIOA_MODER &= ~(3U << 10);   // Clear bits 11:10
	GPIOA_MODER |=  (1U << 10);   // Set 01 → output above line is for before set bit clear that

	while(1){
		// 3. Toggle LED
		GPIOA_ODR ^= (1U << 5);
		//delay is must for on and off the led it is o and 1
		delay();
	}

}
