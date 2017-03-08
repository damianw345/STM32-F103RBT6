/*
 * tb6612.h
 *
 *  Created on: 21 gru 2016
 *      Author: samsung
 */

#ifndef DC_MOTOR_TB6612_H_
#define DC_MOTOR_TB6612_H_

#include "stm32f10x_gpio.h"
#include "pwm.h"
/*****************INPUT_A***********************/
#define INPUTa1PORT GPIOB
#define INPUTa2PORT GPIOC

#define INPUTA1 GPIO_Pin_8//PB8 <- PC6 nie chcial dzialac, chyba go USZKODZILEM
#define INPUTA2 GPIO_Pin_7//PC7
/***********************************************/

/******************INPUT_B**********************/
#define INPUTb1PORT GPIOC
#define INPUTb2PORT GPIOB

#define INPUTB1 GPIO_Pin_8//PC8
#define INPUTB2 GPIO_Pin_1//PB1
/***********************************************/

/*******************PWM*************************/
#define PWM_INPUTA GPIO_Pin_8//PA8 - PWM_A
#define PWM_INPUTB GPIO_Pin_11//PA11 - PWM_B

void Initialize_HBridge();

/***********************************MotorA control functions***********************************************/
void MotorA_TurnRight(uint16_t pwm_pulseWidth);
void MotorA_TurnLeft(uint16_t pwm_pulseWidth);
void MotorA_Stop();
void SpeedRegulatorMotorALeft(uint16_t req_RPS);
void SpeedRegulatorMotorARight(uint16_t req_RPS);

/***********************************MotorB control functions*************************************************/
void MotorB_TurnRight(uint16_t pwm_pulseWidth);
void MotorB_TurnLeft(uint16_t pwm_pulseWidth);
void MotorB_Stop();
void SpeedRegulatorMotorBLeft(uint16_t req_RPS);
void SpeedRegulatorMotorBRight(uint16_t req_RPS);
/*************************************************************************************************************/

#endif /* DC_MOTOR_TB6612_H_ */
