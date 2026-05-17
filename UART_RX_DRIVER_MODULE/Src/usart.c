/*
 * usart.c
 *
 *  Created on: 15-May-2026
 *      Author:Chaithra
 */
#include <stdint.h>
#include "stm32f0xx.h"
#include <stdio.h>
/* ===================== MACROS ===================== */

// Enable clock for GPIOA
#define GPIOA_EN    (1U << 17)

// Enable clock for USART2 (APB1 bus)
#define USART2_EN   (1U << 17)

// Peripheral clock frequency (default HSI = 8 MHz)
#define PERIPHERAL_CLK 8000000

// Desired UART baud rate
#define BAUD_RATE      115200

// USART Control Register bits
#define UART_RX_EN (1U << 2)   // receiver enable
#define UART_EN    (1U << 0)   // USART enable


/* ===================== FUNCTION: BAUD RATE ===================== */
/*
 * Function to compute BRR (Baud Rate Register) value
 *
 * Formula:
 *      BRR = Peripheral Clock / Baud Rate
 *
 * Rounded calculation used for better accuracy
 */
static uint32_t computeBaudrate(uint32_t periphclk, uint32_t baudrate)
{
    return ((periphclk + (baudrate / 2)) / baudrate);
}


/* ===================== FUNCTION: RECIVE ===================== */
/*
 *RECIEVE one character over UART
 *
 * Steps:
 * 1. Wait until RXNE (RECEIVE Data Register Empty) is set
 * 2. Read Data register
 */
char uartReceive(void)
{
    // Wait until receive register is not empty
    while (!(USART2->ISR & (1U << 5)));   // RXNE flag

    // Return the data from data register
    return USART2->RDR;
}

void uartInit(){
	/* =====================================================
	     * Step 1: Enable Clock for GPIOA
	     * -----------------------------------------------------
	     * Required before configuring GPIO registers
	     * ===================================================== */
	    RCC->AHBENR |= GPIOA_EN;
	    /* =====================================================
	     * Step 2: Configure PA3 as Alternate Function Rx
	     * -----------------------------------------------------
	     * MODER bits for PA3 -> [7:6]
	     *
	     * 00 = Input
	     * 01 = Output
	     * 10 = Alternate Function
	     * 11 = Analog
	     * ===================================================== */

	    // Clear bits
	    GPIOA->MODER &= ~(3U << (3 * 2)); //This is like 3 pos 2 bits

	    // Set Alternate Function mode (10)
	    GPIOA->MODER |=  (2U << (3 * 2));


	    /* =====================================================
	     * Step 3: Configure Alternate Function for PA3
	     * -----------------------------------------------------
	     * AFRL register controls pins 0–7
	     *
	     * PA3 uses bits [12:15]
	     *
	     * AF1 -> USART2_RX
	     * ===================================================== */

	    // Clear 4 bits
	    /*Each pin uses 4 bits in AFR register. First I clear those 4 bits using mask (0xF),
	     then I set the required alternate function value using bit shifting.*/
	    GPIOA->AFR[0] &= ~(0xf << (3 * 4));

	    // Set AF1 (0001)
	    GPIOA->AFR[0] |=  (1U << (3 * 4)); //setting value 1 to bit 12


	    /* =====================================================
	     * Step 4: Enable USART2 Clock
	     * ===================================================== */
	    RCC->APB1ENR |= USART2_EN;


	    /* =====================================================
	     * Step 5: Configure Baud Rate
	     * ===================================================== */
	    USART2->BRR = computeBaudrate(PERIPHERAL_CLK, BAUD_RATE);


	    /* =====================================================
	     * Step 6: Enable UART Transmitter and UART
	     * ===================================================== */
	    // Enable Reciver
	    USART2->CR1 |= UART_RX_EN;

	    // Enable USART
	    USART2->CR1 |= UART_EN;

}



void ledInit()
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

}
