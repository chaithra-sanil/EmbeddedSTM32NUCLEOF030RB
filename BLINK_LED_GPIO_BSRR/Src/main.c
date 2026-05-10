/*
 * File        : main.c
 * Author      : Chaithra
 * Description : Turn ON User LED (PA5) on STM32F030R8 using Bare-Metal (Register Level)
 *
 * Board       : STM32 NUCLEO-F030R8
 * LED Pin     : PA5
 *
 * Concept Used:
 * 1. Memory-Mapped I/O
 * 2. Register-level programming (Bare Metal)
 * 3. CMSIS-style structure for peripheral access
 *
 * Steps:
 * 1. Enable GPIOA clock using RCC
 * 2. Configure PA5 as OUTPUT using MODER register
 * 3. Set PA5 HIGH using ODR register
 *
 * Note:
 * - No HAL / No libraries used
 * - Direct hardware control using registers
 */

#include <stdint.h>
#include <STM32F0xx.h>


/* ===================== MAIN FUNCTION ===================== */

int main(void)
{
    /* -------- Step 1: Enable GPIOA Clock -------- */
    /*
     * RCC_AHBENR bit 17 controls GPIOA clock.
     * 1 = Enable clock
     */
     RCC->AHBENR |= (1U << 17);


    /* -------- Step 2: Configure PA5 as Output -------- */
    /*
     * Each pin uses 2 bits in MODER register.
     * PA5 → bits [11:10]
     *
     * 00 = Input
     * 01 = Output
     * 10 = Alternate Function
     * 11 = Analog
     */

    // Clear bits [11:10]
    GPIOA->MODER &= ~(3U << 10);

    // Set output mode (01)
    GPIOA->MODER |=  (1U << 10);

    /* -------- Infinite Loop -------- */
    while (1)
    {
    	 /* -------- Step 3: Set PA5 HIGH (Turn ON LED) -------- */
    	GPIOA->BSRR |= (1U << 5);
    	for(int i=0;i<100000;i++);
    	GPIOA->BSRR |= (1U<<21);
    	for(int i=0;i<100000;i++);
    }
}
