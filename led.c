/*
 * led.c
 *
 *  Created on: 14 wrz 2016
 *      Author: samsung
 */

#include "led.h"

void Initialize_LED()
{
	GPIO_InitTypeDef gpio;

	//konfiguracja diody na plytce
	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_5;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &gpio);
}
