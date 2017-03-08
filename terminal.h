/*
 * terminal.h
 *
 *  Created on: 14 wrz 2016
 *      Author: samsung
 */

#ifndef TERMINAL_H_
#define TERMINAL_H_

#include "stm32f10x.h"
//#include "fifo.h"
#include <stdio.h> //uzyj do printfa

void Initialize_UART(void);

void UART_SendChar(USART_TypeDef * USARTx, char c);
void UART_SendString(USART_TypeDef * USARTx, char* s);

char UART_GetChar(USART_TypeDef * USARTx);

//int __io_putchar(int c);

#endif /* TERMINAL_H_ */
