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

/* ===================== BASE ADDRESSES ===================== */

// RCC base address (Reset and Clock Control)
#define RCC_BASE       0x40021000UL

// GPIOA base address
#define GPIOA_BASE     0x48000000UL


/* ===================== RCC REGISTER ===================== */

// AHB Peripheral Clock Enable Register (offset: 0x14)
#define RCC_AHBENR     (*(volatile uint32_t *)(RCC_BASE + 0x14))


/* ===================== GPIO STRUCTURE ===================== */
/*
 * Structure representing GPIO registers.
 * Each register is 32-bit and placed sequentially in memory.
 */
typedef struct {
    volatile uint32_t MODER;   // Mode register (offset 0x00)
    volatile uint32_t OTYPER;  // Output type (offset 0x04)
    volatile uint32_t OSPEEDR; // Output speed (offset 0x08)
    volatile uint32_t PUPDR;   // Pull-up/pull-down (offset 0x0C)
    volatile uint32_t IDR;     // Input data register (offset 0x10)
    volatile uint32_t ODR;     // Output data register (offset 0x14)
    volatile uint32_t BSRR;    // Bit set/reset register (offset 0x18)
    volatile uint32_t LCKR;    // Lock register (offset 0x1C)
    volatile uint32_t AFRL;    // Alternate function low (offset 0x20)
    volatile uint32_t AFRH;    // Alternate function high (offset 0x24)
    volatile uint32_t BRR;     // Bit reset register (offset 0x28)
} GPIO_TypeDef;


/* Pointer to GPIOA base address */
#define GPIOA   ((GPIO_TypeDef *) GPIOA_BASE)


/* ===================== MAIN FUNCTION ===================== */

int main(void)
{
    /* -------- Step 1: Enable GPIOA Clock -------- */
    /*
     * RCC_AHBENR bit 17 controls GPIOA clock.
     * 1 = Enable clock
     */
    RCC_AHBENR |= (1U << 17);


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


    /* -------- Step 3: Set PA5 HIGH (Turn ON LED) -------- */
    /*
     * ODR register controls output value.
     * Writing 1 to bit 5 → Pin HIGH → LED ON
     */
    GPIOA->ODR |= (1U << 5);


    /* -------- Infinite Loop -------- */
    while (1)
    {
        // Do nothing → keep LED ON
    }
}
