/*
 * File        : main.c
 * Author      : Chaithra
 *
 * Description :
 *      Transmit character 'A' continuously using USART2 (UART)
 *      on STM32F030R8 using Bare-Metal Programming.
 *
 * Board       : STM32 NUCLEO-F030R8
 *
 * Peripheral Used:
 *      - USART2 (TX only)
 *      - GPIOA (PA2 as TX pin)
 *
 * Pin Configuration:
 *      PA2 -> USART2_TX (Alternate Function AF1)
 *
 * Concepts Used:
 *      1. GPIO Alternate Function configuration
 *      2. USART (UART) transmission
 *      3. Baud rate calculation
 *      4. Register-level programming (Bare Metal)
 *      5. CMSIS-based peripheral access
 *
 * Working:
 *      - UART is configured at 115200 baud rate
 *      - Character 'A' is transmitted continuously
 *      - Output can be seen on serial terminal (Tera Term / PuTTY)
 *
 * Note:
 *      - System clock assumed: 8 MHz (default HSI)
 *      - No HAL functions used
 *      - Direct register access using CMSIS
 */


#include <stdint.h>
#include "stm32f0xx.h"
#include <stdio.h>
#include "usart.h"

/* ===================== MAIN FUNCTION ===================== */

int main(void)
{
	 uartInit();

    /* =====================================================
     * Step 7: Transmit Data Continuously
     * ===================================================== */
    while (1)
    {
        printf("Hello usart tx code\n\r");
        // Small delay to avoid flooding terminal
        for (volatile int i = 0; i < 100000; i++);
    }
}
