/*
 * maestro.h
 *
 *  Created on: 18 gru 2016
 *      Author: samsung
 */

#ifndef MAESTRO_H_
#define MAESTRO_H_

#include "terminal.h"

#define MAESTRO_SET_TARGET_CMD 			0x84
#define MAESTRO_SET_SPEED_CMD 			0x87
#define MAESTRO_SET_ACCELERATION_CMD	0x89
#define MAESTRO_GET_POSITION_CMD		0x90
#define MAESTRO_GET_MOVING_STATE_CMD	0x93
#define MAESTRO_GET_ERRORS_CMD			0xA1
#define MAESTRO_GO_HOME					0xA2

/*****************************************MAESTRO "PUBLIC" FUNCTIONS******************************************/
void MAESTRO_SetPosition(USART_TypeDef* USARTx, uint8_t channel_num,uint8_t degree);
//void MAESTRO_Rotate_X_Degrees(USART_TypeDef* USARTx, uint8_t channel_num,uint8_t degrees, int8_t direction);
//void MAESTRO_GoHomeCmd(USART_TypeDef* USARTx);

/*****************************************MAESTRO "PRIVATE" FUNCTIONS*****************************************/
void MAESTRO_SetTarget(USART_TypeDef* USARTx,uint8_t cmd, uint8_t channel_num, uint16_t target);
void MAESTRO_SendCommand(USART_TypeDef* USARTx, uint8_t cmd, uint8_t channel_num, uint8_t low_bits, uint8_t high_bits);
uint16_t MAESTRO_ReceiveData(USART_TypeDef* USARTx,uint8_t cmd, uint8_t channel_num);
/************************************************************************************************************/


#endif /* MAESTRO_H_ */
