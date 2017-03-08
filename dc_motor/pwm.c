/*
 * Timer initialization library
 *
 * Example configuration
 *  //initialize RCCs
	Initialize_GPIO_RCC();
	Initialize_PWM_RCC();

	//initialize TIM & GPIO for PWM
	Initialize_GPIOx(GPIOB, GPIO_Pin_6, GPIO_Mode_AF_PP);
	Initialize_TIMx(TIM4,TIM_CounterMode_Up,1000-1,1280-1);
	Initialize_TIMxChanelx(TIM4,1,TIM_OCMode_PWM1,TIM_OutputState_Enable,50);
 */

#include "dc_motor/pwm.h"

/*zwyczajna hipsterka*/
#define RCC_APB2Periph_TIM(x) XRCC_APB2Periph_TIM(x)
#define XRCC_APB2Periph_TIM(x) (RCC_APB2Periph_TIM##x)

/*choose TIMx RCC to be configured*/
#define TIM_NUMBER 1

void Initialize_TIM_RCC()
{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM(TIM_NUMBER), ENABLE);
}

void Initialize_PWM_PINS(GPIO_TypeDef * GPIOx,uint16_t GPIO_Pins)
{
	GPIO_InitTypeDef gpio;
	GPIO_StructInit(&gpio);

	gpio.GPIO_Pin = GPIO_Pins;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &gpio);
}

void Initialize_TIMx(TIM_TypeDef * TIMx,uint16_t TIM_CounterMod,uint16_t prescaler, uint16_t period)
{
	TIM_TimeBaseInitTypeDef timeBaseStruct;

	TIM_TimeBaseStructInit(&timeBaseStruct);
	timeBaseStruct.TIM_Period = period;
	timeBaseStruct.TIM_Prescaler = prescaler;
	timeBaseStruct.TIM_CounterMode = TIM_CounterMod;
	TIM_TimeBaseInit(TIMx,&timeBaseStruct);

	TIM_Cmd(TIMx,ENABLE);

	#if TIM_NUMBER == 1
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	#endif
}

void Initialize_TIMxChanelx(TIM_TypeDef * TIMx,uint8_t TIMx_channel,uint16_t TIM_OCmode,uint16_t TIM_Output,uint16_t pulse)
{
	TIM_OCInitTypeDef ocInitStruct;

	TIM_OCStructInit(&ocInitStruct);
	ocInitStruct.TIM_OCMode = TIM_OCmode;
	ocInitStruct.TIM_OutputState = TIM_Output;
	ocInitStruct.TIM_Pulse = pulse;

	switch (TIMx_channel)
	{
	case 1:
		TIM_OC1Init(TIMx,&ocInitStruct);
		break;
	case 2:
		TIM_OC2Init(TIMx,&ocInitStruct);
		break;
	case 3:
		TIM_OC3Init(TIMx,&ocInitStruct);
		break;
	case 4:
		TIM_OC4Init(TIMx,&ocInitStruct);
		break;
	}
}

void PWM_SetPulse(TIM_TypeDef * TIMx,uint8_t TIMx_channel,uint16_t pulse)
{
	switch (TIMx_channel)
	{
	/* Set the right Capture Compare Register value */
	case 1:
		TIMx->CCR1 = pulse;
		break;
	case 2:
		TIMx->CCR2 = pulse;
		break;
	case 3:
		TIMx->CCR3 = pulse;
		break;
	case 4:
		TIMx->CCR4 = pulse;
		break;
	}
}

