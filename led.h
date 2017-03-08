/*
 * led.h
 *
 *  Created on: 14 wrz 2016
 *      Author: samsung
 */

#ifndef LED_H_
#define LED_H_

#include "stm32f10x_gpio.h"

#define LED_PORT PORTA
#define LED_PIN  GPIO_Pin_5

void Initialize_LED();

#endif /* LED_H_ */
