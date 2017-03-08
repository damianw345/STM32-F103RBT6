/*
 * config.h
 *
 *  Created on: 3 lip 2016
 *      Author: Andrzej
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "stm32f10x.h"
#include <stdio.h>
#include <stdint.h>

#define TIM_PERIOD 10 // 10us

volatile uint32_t timer;

void Initialize_Timer();
void Initialize_Echo();
void Initialize_Trigger();
void Initialize_Exti();
void Enable_Interrupt();

void Initialize_HCSR04();

#endif /* CONFIG_H_ */
