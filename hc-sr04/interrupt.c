/*
 * interrupt.c
 *
 *  Created on: 3 lip 2016
 *      Author: Damian
 *
 *      ECHO0 LINE10
 *      ECHO1 LINE11
 *      ECHO2 LINE12
 *      ECHO3 LINE9
 */
#include "hc-sr04/interrupt.h"
void EXTI15_10_IRQHandler()
{
	//odczyt licznika timera przy zboczu narastajacym i opadajacym
	//pozwoli to wyliczyc czas trwania impulsu i odleglosc
	if (EXTI_GetITStatus(EXTI_Line10))
	{
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == SET)
		{
			TIM_value_rising[0] = TIM_GetCounter(TIM2);
		}
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == RESET)
		{
			TIM_value_falling[0] = TIM_GetCounter(TIM2);
		}
		EXTI_ClearITPendingBit(EXTI_Line10);
	}

	if (EXTI_GetITStatus(EXTI_Line11))
	{
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == SET)
		{
			TIM_value_rising[1] = TIM_GetCounter(TIM2);
		}
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == RESET)
		{
			TIM_value_falling[1] = TIM_GetCounter(TIM2);
		}
		EXTI_ClearITPendingBit(EXTI_Line11);
	}

	if (EXTI_GetITStatus(EXTI_Line12))
	{

		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12) == SET)
		{
			TIM_value_rising[2] = TIM_GetCounter(TIM2);
		}
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12) == RESET)
		{
			TIM_value_falling[2] = TIM_GetCounter(TIM2);
		}
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
}

void EXTI9_5_IRQHandler()
{
	if (EXTI_GetITStatus(EXTI_Line9))
	{
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9) == SET)
		{
			TIM_value_rising[3] = TIM_GetCounter(TIM2);
		}
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9) == RESET)
		{
			TIM_value_falling[3] = TIM_GetCounter(TIM2);
		}
		EXTI_ClearITPendingBit(EXTI_Line9);
	}
}
