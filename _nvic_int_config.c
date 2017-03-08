/*
 * _nvic_int_config.c
 *
 *  Created on: 14 gru 2016
 *      Author: samsung
 */

#include "_nvic_int_config.h"

//NVIC_PriorityGroup_0 - mozliwosc ustawienia podpriorytetow dla
//poszczegolnych modulow w zakresie <0;15>

void Initialize_NVIC()
{
	NVIC_InitTypeDef nvic;

	/* Ustawienie grupy priorytetów */
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

/*****************************************BLE(USART2)*******************************************************/
	/* Uruchomienie przerwania od USART2 */
	nvic.NVIC_IRQChannel = USART2_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 15;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

/*****************************************HCSR-04(EXTI)*****************************************************/

	nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;//0x00 tak bylo;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

	nvic.NVIC_IRQChannel = EXTI9_5_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority =0;//0x00 tak bylo ostatnio;//0x01 duzo wczesniej tak bylo
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

	/*****************************************(xxxxxxxx)*****************************************************/
}


