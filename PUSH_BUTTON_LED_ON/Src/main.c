/*
 * File        : main.c
 * Author      : Chaithra
 * Description :
 *      Control User LED (PA5) using Push Button (PC13)
 *      on STM32F030R8 using Bare-Metal Programming.
 *
 * Board       : STM32 NUCLEO-F030R8
 *
 * Hardware Used:
 *      - User LED    -> PA5
 *      - Push Button -> PC13
 *
 * Concepts Used:
 *      1. Memory-Mapped I/O
 *      2. GPIO Input Configuration
 *      3. GPIO Output Configuration
 *      4. Register-Level Programming
 *      5. CMSIS Register Access
 *
 * Working:
 *      - When Push Button is PRESSED:
 *              LED turns ON
 *
 *      - When Push Button is RELEASED:
 *              LED turns OFF
 *
 * Registers Used:
 *      RCC->AHBENR   : Enable clock for GPIO ports
 *      GPIOx->MODER  : Configure GPIO pin mode
 *      GPIOx->IDR    : Read input pin value
 *      GPIOx->BSRR   : Set/Reset output pin atomically
 *
 * Note:
 *      - No HAL functions used
 *      - Direct register access using CMSIS
 *      - PC13 is configured as INPUT
 *      - PA5 is configured as OUTPUT
 */

#include <stdint.h>
#include "stm32f0xx.h"


/* ===================== MAIN FUNCTION ===================== */

int main(void)
{
    /* =====================================================
     * Step 1: Enable Clock for GPIOA and GPIOC
     * -----------------------------------------------------
     * GPIO peripherals require clock before use.
     *
     * Bit 17 -> GPIOA clock enable
     * Bit 19 -> GPIOC clock enable
     * ===================================================== */
    RCC->AHBENR |= (1U << 17);
    RCC->AHBENR |= (1U << 19);


    /* =====================================================
     * Step 2: Configure PA5 as OUTPUT
     * -----------------------------------------------------
     * MODER register:
     * Each GPIO pin uses 2 bits.
     *
     * For PA5:
     * Bits -> [11:10]
     *
     * 00 = Input
     * 01 = Output
     * 10 = Alternate Function
     * 11 = Analog
     * ===================================================== */

    // Clear bits [11:10]
    GPIOA->MODER &= ~(3U << (5 * 2));

    // Set PA5 as output mode (01)
    GPIOA->MODER |=  (1U << (5 * 2));


    /* =====================================================
     * Step 3: Configure PC13 as INPUT
     * -----------------------------------------------------
     * For input mode -> MODER bits should be 00
     *
     * PC13 uses bits [27:26]
     * ===================================================== */

    // Clear bits [27:26]
    GPIOC->MODER &= ~(3U << (13 * 2));

    // No need to set bits because 00 = Input mode


    /* =====================================================
     * Step 4: Infinite Loop
     * -----------------------------------------------------
     * Read push button status continuously.
     * ===================================================== */

    while (1)
    {
        /* -------------------------------------------------
         * Read PC13 input using IDR register
         *
         * Condition:
         * If button pressed -> PC13 becomes LOW (0)
         *
         * '!' operator makes condition TRUE when bit = 0
         * ------------------------------------------------- */

        if (!(GPIOC->IDR & (1U << 13)))
        {
            /* ---------------------------------------------
             * Turn ON LED
             *
             * BSRR lower 16 bits -> SET operation
             * Writing 1 to bit 5 sets PA5 HIGH
             * --------------------------------------------- */
            GPIOA->BSRR = (1U << 5);
        }
        else
        {
            /* ---------------------------------------------
             * Turn OFF LED
             *
             * BSRR upper 16 bits -> RESET operation
             * Bit (5 + 16) = 21 resets PA5
             * --------------------------------------------- */
            GPIOA->BSRR = (1U << 21);
        }
    }
}
