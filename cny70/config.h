/*
 * config.h
 *
 *  Created on: 14 wrz 2016
 *      Author: samsung
 */

#ifndef CONFIG1_H_
#define CONFIG1_H_

#include "stm32f10x.h"

#define ADC_CHANNELS 3
#define LINE_SPOTTED 4000

uint16_t adc_value[ADC_CHANNELS];

void Initialize_DMA();
void Initialize_ADC();
//void Initialize_RCC();

#endif /* CONFIG1_H_ */
