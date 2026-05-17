/*
 * File        : systick.c
 * Author      : Chaithra
 *
 * Description :
 *      This file implements delay functionality using the SysTick timer
 *      available in ARM Cortex-M microcontrollers.
 *
 * Purpose of SysTick:
 *      - SysTick is a 24-bit down counter (timer)
 *      - Used for generating accurate time delays
 *      - Commonly used in RTOS and bare-metal applications
 *
 * Why SysTick Instead of for-loop Delay?
 *      - Provides accurate delay based on system clock
 *      - Independent of compiler optimization
 *      - Hardware-based timing (more reliable)
 *
 * System Assumption:
 *      - System clock = 8 MHz (HSI default)
 *
 * Delay Calculation:
 *      - 1 ms delay → 8000 clock cycles (8 MHz)
 *
 * Working:
 *      - LOAD register is set with count value (8000)
 *      - Timer counts down to 0
 *      - COUNTFLAG is set when timer reaches 0
 *      - This process is repeated 'delay' times
 *
 * Example:
 *      delay_systick(1000); → ~1 second delay
 */

#include "stm32f0xx.h"

/* ===================== MACROS ===================== */

// Number of clock cycles for 1 ms delay (8 MHz clock)
#define SYSTICK_LOAD    8000

// SysTick Control Register Bits
#define CLKSOURCE       (1U << 3)   // Use processor clock (AHB)
#define SYSTICK_ENABLE  (1U << 0)   // Enable SysTick timer
#define COUNTFLAG       (1U << 16)  // Timer reached 0


/* ===================== FUNCTION ===================== */

/*
 * Function Name : delay_systick
 * Description   : Generates delay in milliseconds using SysTick timer
 *
 * Parameters    :
 *      delay → number of milliseconds to delay
 *
 * Return        : None
 *
 * Working:
 *      - Sets SysTick timer for 1 ms
 *      - Waits until timer completes (COUNTFLAG set)
 *      - Repeats for given delay value
 */
void delay_systick(int delay)
{
    /* Load value for 1 ms delay */
    SysTick->LOAD = SYSTICK_LOAD;

    /* Clear current value register */
    SysTick->VAL = 0;

    /* Enable SysTick with processor clock */
    SysTick->CTRL = SYSTICK_ENABLE | CLKSOURCE;

    /* Repeat delay 'delay' times */
    for (int i = 0; i < delay; i++)
    {
        /* Wait until COUNTFLAG is set (timer reaches 0) */
        while ((SysTick->CTRL & COUNTFLAG) == 0);
    }

    /* Disable SysTick timer */
    SysTick->CTRL = 0;
}
