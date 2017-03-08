/*
 * tb6612.c
 *
 *  Created on: 21 gru 2016
 *      Author: samsung
 */

#include "dc_motor/tb6612.h"
#include "gpio.h"
#include "dc_motor/pid.h"

#define MIN_PULSE_0 0
#define MAX_PULSE_1000 1000

extern volatile uint16_t RPS_A;
extern volatile uint16_t RPS_B;

void Initialize_HBridge()
{
	/*Initialize RCCs*/
//	Initialize_GPIO_RCC();
	Initialize_TIM_RCC();

	/*Initialize control pins*/
	Initialize_GPIOx(GPIOC, INPUTA2 | INPUTB1,GPIO_Mode_Out_PP,GPIO_Speed_2MHz);
	Initialize_GPIOx(GPIOB,INPUTA1|INPUTB2,GPIO_Mode_Out_PP,GPIO_Speed_2MHz);

	/*Initialize PWM control pins - TIM1 Channel1,Channel2*/
	Initialize_PWM_PINS(GPIOA, PWM_INPUTA|PWM_INPUTB);

	/*Initialize TIM1*/
	Initialize_TIMx(TIM1,TIM_CounterMode_Up,4,1000);//f_pwm = 16 kHz
	Initialize_TIMxChanelx(TIM1,1,TIM_OCMode_PWM1,TIM_OutputState_Enable,5);
	Initialize_TIMxChanelx(TIM1,4,TIM_OCMode_PWM1,TIM_OutputState_Enable,5);
}
/*************************************************************************************************************/
/*MotorA control functions.
*pwm_pulseWidth range <0;1000>. Set pwm_pulseWidth = 1000 for full speed
*/
void MotorA_TurnRight(uint16_t pwm_pulseWidth)
{
	if(pwm_pulseWidth >MAX_PULSE_1000) pwm_pulseWidth =MAX_PULSE_1000;
	GPIO_SetBits(INPUTa1PORT,INPUTA1);
	GPIO_ResetBits(INPUTa2PORT,INPUTA2);
	PWM_SetPulse(TIM1,1,pwm_pulseWidth);
}

void MotorA_TurnLeft(uint16_t pwm_pulseWidth)
{
	if(pwm_pulseWidth >MAX_PULSE_1000) pwm_pulseWidth =MAX_PULSE_1000;
	GPIO_ResetBits(INPUTa1PORT,INPUTA1);
	GPIO_SetBits(INPUTa2PORT,INPUTA2);
	PWM_SetPulse(TIM1,1,pwm_pulseWidth);
}

void MotorA_Stop()
{
	GPIO_ResetBits(INPUTa1PORT,INPUTA1);
	GPIO_ResetBits(INPUTa2PORT,INPUTA2);
	PWM_SetPulse(TIM1,1,MAX_PULSE_1000);//ENABLE output set to HIGH by 100% PWM filling
}
/*************************************************************************************************************/
void SpeedRegulatorMotorALeft(uint16_t req_RPS)
{
	uint16_t pwm_val =0;

	pwm_val = PID(req_RPS,RPS_A);
	MotorA_TurnLeft(pwm_val);
}

void SpeedRegulatorMotorARight(uint16_t req_RPS)
{
	uint16_t pwm_val =0;

	pwm_val = PID(req_RPS,RPS_A);
	MotorA_TurnRight(pwm_val);
}

/*************************************************************************************************************/
/*MotorB control functions*/
void MotorB_TurnRight(uint16_t pwm_pulseWidth)
{
	if(pwm_pulseWidth >MAX_PULSE_1000) pwm_pulseWidth =MAX_PULSE_1000;
	GPIO_SetBits(INPUTb1PORT,INPUTB1);
	GPIO_ResetBits(INPUTb2PORT,INPUTB2);

	PWM_SetPulse(TIM1,4,pwm_pulseWidth);
}

void MotorB_TurnLeft(uint16_t pwm_pulseWidth)
{
	if(pwm_pulseWidth >MAX_PULSE_1000) pwm_pulseWidth =MAX_PULSE_1000;
	GPIO_ResetBits(INPUTb1PORT,INPUTB1);
	GPIO_SetBits(INPUTb2PORT,INPUTB2);
	PWM_SetPulse(TIM1,4,pwm_pulseWidth);
}

void MotorB_Stop()
{
	GPIO_ResetBits(INPUTb1PORT,INPUTB1);
	GPIO_ResetBits(INPUTb2PORT,INPUTB2);
	PWM_SetPulse(TIM1,4,MAX_PULSE_1000);//ENABLE output set to HIGH by 100% PWM filling
}
/*************************************************************************************************************/

void SpeedRegulatorMotorBLeft(uint16_t req_RPS)
{
	uint16_t pwm_val =0;

	pwm_val = PID(req_RPS,RPS_B);
	MotorB_TurnLeft(pwm_val);
}

void SpeedRegulatorMotorBRight(uint16_t req_RPS)
{
	uint16_t pwm_val =0;

	pwm_val = PID(req_RPS,RPS_B);
	MotorB_TurnRight(pwm_val);
}
/*************************************************************************************************************/

