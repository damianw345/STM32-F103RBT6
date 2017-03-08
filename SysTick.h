/*
 * SysTick.h
 *
 *  Created on: 14 wrz 2016
 *      Author: samsung
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "stm32f10x.h"

/*Choose time base for SysTickHandler*/
#define TIME_BASE_ms
//#define TIME_BASE_us
//#define TIME_BASE_10ms

volatile uint32_t timer;

void Initialize_SysTick();
void SysTick_Handler();
void delay(uint32_t time);

#endif /* SYSTICK_H_ */
