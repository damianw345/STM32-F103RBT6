/*
 * gpio.c
 *
 *  Created on: 27 wrz 2016
 *      Author: samsung
 */

#include "gpio.h"

void Initialize_GPIOx(GPIO_TypeDef * GPIOx, uint16_t GPIO_Pins, GPIOMode_TypeDef mode,uint8_t GPIO_Speed_xMHz)
{
	GPIO_InitTypeDef gpio;

	GPIO_StructInit(&gpio);
	gpio.GPIO_Mode = mode;
	gpio.GPIO_Pin = GPIO_Pins;
	gpio.GPIO_Speed = GPIO_Speed_xMHz;

	GPIO_Init(GPIOx, &gpio);
}

void Initialize_GPIO_RCC()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
			RCC_APB2Periph_GPIOD ,ENABLE);
}

void Initialize_AFIO_RCC()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}

