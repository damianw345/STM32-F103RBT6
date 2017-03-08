/*
 * config.c
 *
 *  Created on: 13 wrz 2016
 *      Author: samsung
 */

#include "cny70/config.h"

void Initialize_DMA()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_InitTypeDef dma;

	//DMA konfiguracja
	DMA_StructInit(&dma);
	dma.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	dma.DMA_MemoryBaseAddr = (uint32_t)adc_value;
	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	dma.DMA_DIR = DMA_DIR_PeripheralSRC;
	dma.DMA_BufferSize = ADC_CHANNELS;
	dma.DMA_Mode = DMA_Mode_Circular;
	DMA_Init(DMA1_Channel1, &dma);
	DMA_Cmd(DMA1_Channel1, ENABLE);
}

void Initialize_ADC()
{
	GPIO_InitTypeDef gpio;
	ADC_InitTypeDef adc;

	 //konfiguracja parametrów próbkowania ADC
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	 	ADC_RegularChannelConfig(ADC1,ADC_Channel_10, 1,ADC_SampleTime_71Cycles5);
		ADC_RegularChannelConfig(ADC1,ADC_Channel_11, 2,ADC_SampleTime_71Cycles5);
		ADC_RegularChannelConfig(ADC1,ADC_Channel_12, 3,ADC_SampleTime_71Cycles5);

	 //ADC Analog LINES
	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	gpio.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &gpio);

	//ADC konfiguracja
	ADC_StructInit(&adc);
	adc.ADC_ScanConvMode = ENABLE;
	adc.ADC_ContinuousConvMode = ENABLE;
	adc.ADC_NbrOfChannel = ADC_CHANNELS;
	adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_Init(ADC1, &adc);

	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);

	 //ADC kalibracja
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));

	 //ADC START
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
