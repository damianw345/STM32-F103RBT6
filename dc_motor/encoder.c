/*
 * Uses TIM3 and TIM4 for encoder purposes
 */

#include "stm32f10x.h"
#include "dc_motor/encoder.h"

volatile uint16_t RPS_A = 0;
volatile uint16_t RPS_B = 0;

volatile uint8_t i = 0;
volatile uint16_t tmpA1 = 0;
volatile uint16_t tmpA2 = 0;
volatile uint16_t tmpB1 = 0;
volatile uint16_t tmpB2 = 0;

/**************************************************************************************/

void Initialize_Encoders()
{
	Encoder_RCC_Configuration();
	Encoder_GPIO_Configuration();
	Encoder_TIM3_Configuration();
	Encoder_TIM4_Configuration();

	Encoder_SysTick_Configuration();
}

/**************************************************************************************/
void Encoder_RCC_Configuration(void)
{
    // clock for GPIO
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE);

    // clock for TIM3 and TIM4
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4, ENABLE);
}
/**************************************************************************************/
void Encoder_GPIO_Configuration(void)
{
    GPIO_InitTypeDef gpio;

    //PA6 TIM3_CH1, PA7 TIM3_CH2
    gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpio);

    //PB6 TIM4_CH1, PB7 TIM4_CH2
    gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &gpio);

}
/**************************************************************************************/
void Encoder_TIM3_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_Period = 65535; // Maximal
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    // TIM_EncoderMode_TI1: Counter counts on TI1FP1 edge depending on TI2FP2 level.
    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI1, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

    TIM_Cmd(TIM3, ENABLE);
}

/**************************************************************************************/
void Encoder_TIM4_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_Period = 65535;// maximal
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    // TIM_EncoderMode_TI1: Counter counts on TI1FP1 edge depending on TI2FP2 level.
    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI1, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

    TIM_Cmd(TIM4, ENABLE);
}
/**************************************************************************************/
void Encoder_SysTick_Configuration()
{
	SysTick_Config(SystemCoreClock/100);// write 100 for 10ms, 10 for 100ms
}
/**************************************************************************************/

void SysTick_Handler()
{
	//execute commands alternately.
	//i == 0 -> beginning of period
	i = i%2;
	if(i == 0)
	{
		tmpA1 = TIM3->CNT;
		tmpB1 = TIM4->CNT;
	}

	//i == 1 -> end of period
	if(i == 1)
	{
		tmpA2 = TIM3->CNT;
		tmpB2 = TIM4->CNT;

		//compute RPS = (TIM_CNT_START - TIM_CNT_END) * 10/1920
		//period is 100ms; to get the value of 1 sec multiply by 10, to get the value of 1 minute mul by 60
		//1920 is encoder's full rotation value
		//always subtract from bigger value
//		RPS_A = ( (tmpA1 < tmpA2) ? (tmpA2 - tmpA1) : (tmpA1 - tmpA2) )*1000/192;
//		RPS_B = ( (tmpB1 < tmpB2) ? (tmpB2 - tmpB1) : (tmpB1 - tmpB2) )*1000/192;

		RPS_A = ( (tmpA1 < tmpA2) ? (tmpA2 - tmpA1) : (tmpA1 - tmpA2) )*125/4;
		RPS_B = ( (tmpB1 < tmpB2) ? (tmpB2 - tmpB1) : (tmpB1 - tmpB2) )*125/4;

	}
	i++;//TERAZ BEDE MIAL ODCZYT Z 10ms
}
/**************************************************************************************/

//		ms10A++;
//		ms10B++;
//
//	if(rotationA == complete)
//	{
//		//compute Rotations Per Second
//		RPS_A = ONE_SECOND/ms10A;
//		ms10A = 0;
//		rotationA = incomplete;
//	}
//
//	if(rotationB == complete)
//	{
//		//compute Rotations Per Second (a.k.a. frequency)
//		RPS_B = ONE_SECOND/ms10B;
//		ms10B =0;
//		rotationB = incomplete;
//	}
/**************************************************************************************/

//void Encoder_Interrupts_Configuration()
//{
//	NVIC_InitTypeDef nvic;
//	nvic.NVIC_IRQChannel = TIM3_IRQn;
//	nvic.NVIC_IRQChannelCmd = ENABLE;
//	nvic.NVIC_IRQChannelPreemptionPriority = 0;
//	nvic.NVIC_IRQChannelSubPriority = 0;
//
//	NVIC_Init(&nvic);
//
//	nvic.NVIC_IRQChannel = TIM4_IRQn;
//	nvic.NVIC_IRQChannelCmd = ENABLE;
//	nvic.NVIC_IRQChannelPreemptionPriority = 0;
//	nvic.NVIC_IRQChannelSubPriority = 1;
//
//	NVIC_Init(&nvic);
//
//	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
//	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
//}

/**************************************************************************************/

//void TIM3_IRQHandler()
//{
//	//interrupt after TIM3 CNT overflow indicates full wheel A rotation
//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
//	{
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
//		rotationA = complete;
//	}
//}
///**************************************************************************************/
//
//void TIM4_IRQHandler()
//{
//	//interrupt after TIM4 CNT overflow indicates full wheel B rotation
//	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
//	{
//		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
//		rotationB = complete;
//	}
//}
