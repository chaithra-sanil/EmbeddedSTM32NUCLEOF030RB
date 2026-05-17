/*
 * usart.c
 *
 *  Created on: 15-May-2026
 *      Author:Chaithra
 */
#include <stdint.h>
#include "stm32f0xx.h"
#include <stdio.h>

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
