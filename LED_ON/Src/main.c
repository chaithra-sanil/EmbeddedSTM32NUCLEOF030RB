/*
 * Program: Turn ON User LED (PA5) in STM32F030R8 using Bare Metal
 *
 * Steps:
 *
 * 1. Identify the LED pin:
 *    - User LED is connected to PA5 (Port A, Pin 5)
 *
 * 2. Enable clock for GPIOA:
 *    - GPIO peripherals require clock to operate
 *    - Use RCC (Reset and Clock Control) register
 *    - Enable GPIOA clock by setting bit in RCC_AHBENR register
 *
 * 3. Find base addresses:
 *    - RCC base address → from memory map
 *    - GPIOA base address → from reference manual
 *
 * 4. Calculate register addresses:
 *    - RCC_AHBENR = RCC base address + offset
 *    - GPIOA_MODER = GPIOA base + offset
 *    - GPIOA_ODR   = GPIOA base + offset
 *
 * 5. Configure PA5 as output:
 *    - Each pin uses 2 bits in MODER
 *    - Set PA5 mode to "01" (output mode)
 *
 * 6. Set PA5 HIGH:
 *    - Write 1 to bit 5 of GPIOA_ODR
 *    - This turns ON the LED
 *
 * 7. Keep program running:
 *    - Use infinite loop
 */


#include <stdint.h>

#define RCC_BASE  0x40021000UL //UL means datatype unsigned long
#define GPIOA_BASE 0x48000000UL

#define RCC_AHBENR *(volatile uint32_t *)(RCC_BASE + 0x14) //DEFRENCE POINTER
#define GPIOA_MODER *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE +  0x14)


int main(void)
{
    // 1. Enable GPIOA clock
    RCC_AHBENR |= (1U << 17);

    // 2. Set PA5 as output (clear then set)
    GPIOA_MODER &= ~(3U << 10);   // Clear bits 11:10
    GPIOA_MODER |=  (1U << 10);   // Set 01 → output above line is for before set bit clear that

    // 3. Turn ON LED
    GPIOA_ODR |= (1U << 5);
    //Loop to keep Led ON
    for(; ;);
}
