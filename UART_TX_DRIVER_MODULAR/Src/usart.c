/*
 * usart.c
 *
 *  Created on: 15-May-2026
 *      Author: Crest0048
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
#define UART_TX_EN (1U << 3)   // Transmitter enable
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


/* ===================== FUNCTION: TRANSMIT ===================== */
/*
 * Transmits one character over UART
 *
 * Steps:
 * 1. Wait until TXE (Transmit Data Register Empty) is set
 * 2. Write data to TDR register
 */
void transmit(char data)
{
    // Wait until transmit register is empty
    while (!(USART2->ISR & (1U << 7)));   // TXE flag

    // Load data into transmit register
    USART2->TDR = data;
}

void uartInit(){
	/* =====================================================
	     * Step 1: Enable Clock for GPIOA
	     * -----------------------------------------------------
	     * Required before configuring GPIO registers
	     * ===================================================== */
	    RCC->AHBENR |= GPIOA_EN;

	    /* =====================================================
	     * Step 2: Configure PA2 as Alternate Function
	     * -----------------------------------------------------
	     * MODER bits for PA2 -> [5:4]
	     *
	     * 00 = Input
	     * 01 = Output
	     * 10 = Alternate Function
	     * 11 = Analog
	     * ===================================================== */

	    // Clear bits
	    GPIOA->MODER &= ~(3U << (2 * 2));

	    // Set Alternate Function mode (10)
	    GPIOA->MODER |=  (2U << (2 * 2));


	    /* =====================================================
	     * Step 3: Configure Alternate Function for PA2
	     * -----------------------------------------------------
	     * AFRL register controls pins 0–7
	     *
	     * PA2 uses bits [11:8]
	     *
	     * AF1 -> USART2_TX
	     * ===================================================== */

	    // Clear 4 bits
	    GPIOA->AFR[0] &= ~(0xF << (2 * 4));

	    // Set AF1 (0001)
	    GPIOA->AFR[0] |=  (1U << (2 * 4));


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

	    // Enable Transmitter
	    USART2->CR1 |= UART_TX_EN;

	    // Enable USART
	    USART2->CR1 |= UART_EN;

}

int __io_putchar(int ch){
	transmit(ch);
	return ch;
}
