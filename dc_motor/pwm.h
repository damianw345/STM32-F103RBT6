/*
 * pwm.h
 *
 *  Created on: 26 wrz 2016
 *      Author: samsung
 */

#ifndef PWM_H_
#define PWM_H_

#include "stm32f10x.h"

void Initialize_TIM_RCC();
void Initialize_TIMx(TIM_TypeDef * TIMx,uint16_t TIM_CounterMod,uint16_t prescaler, uint16_t period);
void Initialize_TIMxChanelx(TIM_TypeDef * TIMx,uint8_t TIMx_channel,uint16_t TIM_OCmode,uint16_t TIM_Output,uint16_t pulse);
void Initialize_PWM_PINS(GPIO_TypeDef * GPIOx,uint16_t GPIO_Pins);

void PWM_SetPulse(TIM_TypeDef * TIMx,uint8_t TIMx_channel,uint16_t pulse);


#endif /* PWM_H_ */
