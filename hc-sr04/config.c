#include "hc-sr04/config.h"

void Initialize_Timer()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseInitTypeDef tim;
    TIM_OCInitTypeDef oc;
    GPIO_InitTypeDef gpio;

    //time base init
    tim.TIM_Prescaler = 640 - 1; // 64MHz/640 = 100kHz
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    tim.TIM_Period = 6000-1;//okres przepelnienia 60ms (wczesniej bylo 60k)
    tim.TIM_ClockDivision = TIM_CKD_DIV1;
    tim.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &tim);

    //output compare PWM1 mode
    oc.TIM_OCMode = TIM_OCMode_PWM1;
    oc.TIM_OCPolarity = TIM_OCPolarity_High;
    oc.TIM_OutputState = TIM_OutputState_Enable;
    oc.TIM_Pulse = 1; //CCRx = 1 (0??), 10uS HIGH
    TIM_OC2Init(TIM2, &oc);

    TIM_Cmd(TIM2, ENABLE);

    //wspolny TRIGGER pin dla wszystkich czujnikow pod kanalem PB1 TIM3_CH4 - sprzetowa generacja PWM
	gpio.GPIO_Pin = GPIO_Pin_1;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &gpio);

}

void Initialize_Echo()
{
	GPIO_InitTypeDef gpio;
	//ECHO0 PC10, ECHO1 PC11, ECHO2 PC12, ECHO3 PC9
	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = (GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_9);
	gpio.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &gpio);
}

void Initialize_Exti()
{
	EXTI_InitTypeDef exti;
	EXTI_StructInit(&exti);

	//INTERRUPT on RISING/FALLING edge - PC10, PC11, PC12, PC9 - ECHO PINs
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource10);
	exti.EXTI_Line = EXTI_Line10;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource11);
	exti.EXTI_Line = EXTI_Line11;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource12);
	exti.EXTI_Line = EXTI_Line12;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource9);
	exti.EXTI_Line = EXTI_Line9;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);
}

//void Enable_Interrupt()
//{
//	NVIC_InitTypeDef nvic;
//	nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
//	nvic.NVIC_IRQChannelPreemptionPriority = 1;//0x00 tak bylo;
//	nvic.NVIC_IRQChannelSubPriority = 0x00;
//	nvic.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&nvic);
//
//	nvic.NVIC_IRQChannel = EXTI9_5_IRQn;
//	nvic.NVIC_IRQChannelPreemptionPriority =1;//0x00 tak bylo ostatnio;//0x01 duzo wczesniej tak bylo
//	nvic.NVIC_IRQChannelSubPriority = 0x00;
//	nvic.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&nvic);
//}

void Initialize_HCSR04()
{
	Initialize_Timer();
	Initialize_Echo();
	Initialize_Exti();
//	Enable_Interrupt();
}
