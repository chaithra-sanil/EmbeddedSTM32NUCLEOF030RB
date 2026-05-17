/*
 * usart.h
 *
 *  Created on: 15-May-2026
 *      Author: Crest0048
 */

#ifndef USART_H_
#define USART_H_

#include <stdint.h>
#include "stm32f0xx.h"
#include <stdio.h>


void uartInit();
char uartReceive();
void ledInit();
#endif /* USART_H_ */
