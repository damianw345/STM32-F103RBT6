/*
 * gpio.h
 *
 *  Created on: 27 wrz 2016
 *      Author: samsung
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f10x.h"

void Initialize_GPIO_RCC();
void Initialize_GPIOx(GPIO_TypeDef * GPIOx, uint16_t GPIO_Pins, GPIOMode_TypeDef mode,uint8_t GPIO_Speed_xMHz);
void Initialize_AFIO_RCC();

#endif /* GPIO_H_ */
