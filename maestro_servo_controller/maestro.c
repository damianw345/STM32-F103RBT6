/*
 * maestro.c
 *
 *Every function is designed to cooperate with "Compact protocol" which
 *is described in Maestro documentation
 */

#include "maestro_servo_controller/maestro.h"

//#define USE_BAUD_AUTO_DETECT_MODE
#define ONE_DEGREE_VALUE 41.6 		/*Calculate as channelX (max_pulse - min_pulse)*4/180
									 *channelX max and min pulse can be changed in Pololu Maestro Control Center,
									 *tab "Channel Settings" */

#define CHANNEL_X_MIN_PULSE 528*4 	/*change only values before *4 */
#define CHANNEL_X_MAX_PULSE 2400*4

/*****************************************MAESTRO "PUBLIC" FUNCTIONS*******************************************************/
void MAESTRO_SetPosition(USART_TypeDef* USARTx, uint8_t channel_num,uint8_t degree)
{
	/*limit degree to not damage servo*/
	if(degree < 0)
		degree = 0;
	if(degree > 180)
		degree = 180;

	MAESTRO_SetTarget(USARTx,MAESTRO_SET_TARGET_CMD,channel_num,CHANNEL_X_MIN_PULSE + ONE_DEGREE_VALUE * degree);
}

/*****************************************MAESTRO "PRIVATE" FUNCTIONS*******************************************************/

void MAESTRO_SetTarget(USART_TypeDef* USARTx,uint8_t cmd, uint8_t channel_num, uint16_t target)
{
	uint8_t serialBytes[4];

	serialBytes[0] = cmd;
	serialBytes[1] = channel_num;
	serialBytes[2] = target & 0x7F; //lsb
	serialBytes[3] = (target >> 7) & 0x7F;//msb

#ifdef USE_BAUD_AUTO_DETECT_MODE
	UART_SendChar(USARTx,0xAA);//detect baud rate
#endif

	UART_SendChar(USARTx,(char)serialBytes[0]);
	UART_SendChar(USARTx,(char)serialBytes[1]);
	UART_SendChar(USARTx,(char)serialBytes[2]);
	UART_SendChar(USARTx,(char)serialBytes[3]);
}

void MAESTRO_SendCommand(USART_TypeDef* USARTx, uint8_t cmd, uint8_t channel_num, uint8_t low_bits, uint8_t high_bits)
{
	uint8_t serialBytes[4];

	serialBytes[0] = cmd;
	serialBytes[1] = channel_num;
	serialBytes[2] = low_bits;
	serialBytes[3] = high_bits;

#ifdef USE_BAUD_AUTO_DETECT_MODE
	UART_SendChar(USARTx,0xAA);//detect baud rate
#endif

	UART_SendChar(USARTx,(char)serialBytes[0]);
	UART_SendChar(USARTx,(char)serialBytes[1]);
	UART_SendChar(USARTx,(char)serialBytes[2]);
	UART_SendChar(USARTx,(char)serialBytes[3]);
}

uint16_t MAESTRO_ReceiveData(USART_TypeDef* USARTx,uint8_t cmd, uint8_t channel_num)
{
	uint8_t data[2];

#ifdef USE_BAUD_AUTO_DETECT_MODE
	UART_SendChar(USARTx,0xAA);//detect baud rate
#endif

	UART_SendChar(USARTx,(char)cmd);
	UART_SendChar(USARTx,(char)channel_num);

	data[0] = UART_GetChar(USARTx);//LSB
	data[1] = UART_GetChar(USARTx);//MSB

	return ((uint16_t) data[1] << 8 | data[0]);
}
/************************************************************************************************************/


//void MAESTRO_Rotate_X_Degrees(USART_TypeDef* USARTx, uint8_t channel_num,uint8_t degrees, int8_t direction)
//{
//	uint16_t target = 0;
//	target = MAESTRO_ReceiveData(USARTx,MAESTRO_GET_POSITION_CMD,channel_num);
//
//	/*prepare to move clockwise*/
//	if(direction>=0)
//		target+= degrees*ONE_DEGREE_VALUE;
//
//	/*prepare to move counterclockwise*/
//	if(direction<0)
//		target-= degrees*ONE_DEGREE_VALUE;
//
//	/*limit target value to not damage servo*/
//	if(target<CHANNEL_X_MIN_PULSE)
//		target = CHANNEL_X_MIN_PULSE;
//	if(target > CHANNEL_X_MAX_PULSE)
//		target = CHANNEL_X_MAX_PULSE;
//
//	MAESTRO_SetTarget(USARTx,MAESTRO_SET_TARGET_CMD,channel_num,target);
//}

//void MAESTRO_GoHomeCmd(USART_TypeDef* USARTx)
//{
//#ifdef USE_BAUD_AUTO_DETECT_MODE
//	UART_SendChar(USARTx,0xAA);//detect baud rate
//#endif
//	UART_SendChar(USARTx,(char)MAESTRO_GO_HOME);
//}
