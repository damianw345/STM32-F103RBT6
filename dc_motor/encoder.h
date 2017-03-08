/*
 * encoder.h
 *
 *  Created on: 16 paü 2016
 *      Author: samsung
 */

#ifndef ENCODER_H_
#define ENCODER_H_

void Initialize_Encoders();

void Encoder_RCC_Configuration();
void Encoder_GPIO_Configuration();
void Encoder_TIM3_Configuration();
void Encoder_TIM4_Configuration();
void Encoder_SysTick_Configuration();
void Encoder_Interrupts_Configuration();

#endif /* ENCODER_H_ */
