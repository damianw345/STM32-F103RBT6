/*
 * calculations.c
 *
 *  Created on: 14 gru 2016
 *      Author: samsung
 */

#include "hc-sr04/calculations.h"

//GLOBAL variables
uint16_t distance[4] = {0};

void HCSR04_CalculateDist()
{
	uint16_t differ;
	for(uint8_t i = 0 ; i<4 ; i++)
	{
		differ = TIM_value_falling[i] - TIM_value_rising[i];
		//abs value
		if(differ<0) differ *= (-1);
		distance[i] =  (differ * TIM_PERIOD)/58;
	}
}
