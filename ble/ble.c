/*
 * ble.c
 *
 *  Created on: 10 paü 2016
 *      Author: samsung
 */

#include "ble/ble.h"
#include "ble/fifo.h"
#include "ble/typedefs.h"

#include "dc_motor/tb6612.h"
#include "maestro_servo_controller/maestro.h"

FIFO_type ble_RXbuf={{},0,0};
FIFO_type ble_TXbuf={{},0,0};

extern volatile t_Flags transfer;

/*************************************************************************************************************/
void BLE_executeIfTransferIsComplete()
{
	//caly napis odebrany
	if(transfer == complete)
    	{
		BLE_readRXbuf(ble_commandBuf);
		BLE_switchCommand();

		//przygotuj flage do ponownego uzycia
		transfer = incomplete;
    	}
}
/*************************************************************************************************************/

/*
 * Commands come from external Android app Bluefruit LE which
 * sends 5 chars in format !Bxyz every time the control pad is
 * touched or released
 * x - pushed button [1:8]
 * y - button state [0:1]
 * z - for every button there is diffrent ending
 * when button is pressed it's value is var, when realesed it's var+1
 */
void BLE_switchCommand()
{
	if(ble_commandBuf[0] == '!' && ble_commandBuf[1] == 'B')
	{
	  switch(ble_commandBuf[2])
	  {
	  case ARROW_UP:
		  if(ble_commandBuf[3] == '1')
		  {
			  GPIO_SetBits(GPIOA,GPIO_Pin_5);
			  MotorA_TurnRight(700);
			  MotorB_TurnRight(700);
		  }
		  else if(ble_commandBuf[3] == '0')
		  {
			  GPIO_ResetBits(GPIOA,GPIO_Pin_5);
			  MotorA_Stop();
			  MotorB_Stop();
		  }
		  break;

	  case ARROW_DOWN:
		  if(ble_commandBuf[3] == '1')
		  {
			  GPIO_SetBits(GPIOA,GPIO_Pin_5);
			  MotorA_TurnLeft(700);
			  MotorB_TurnLeft(700);
		  }
		  else if(ble_commandBuf[3] == '0')
		  {
			  GPIO_ResetBits(GPIOA,GPIO_Pin_5);
			  MotorA_Stop();
			  MotorB_Stop();
		  }
		  break;
	  case ARROW_LEFT:
		  if(ble_commandBuf[3] == '1')
		  {
			  GPIO_SetBits(GPIOA,GPIO_Pin_5);
			  	MAESTRO_SetPosition(USART1,1,0);
			  	MAESTRO_SetPosition(USART1,2,0);
		  }
		  else if(ble_commandBuf[3] == '0')
		  {
			  GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		  }
		  break;
	  case ARROW_RIGHT:
		  if(ble_commandBuf[3] == '1')
		  {
			  GPIO_SetBits(GPIOA,GPIO_Pin_5);
			  	MAESTRO_SetPosition(USART1,1,180);
			  	MAESTRO_SetPosition(USART1,2,180);
		  }
		  else if(ble_commandBuf[3] == '0')
		  {
			  GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		  }
		  break;
	  }
	}
}
/*************************************************************************************************************/

/*read string via USART with interrupts*/
void BLE_readRXbuf(char* str)
{
		while(ble_RXbuf.TailIndex != ble_RXbuf.HeadIndex)
		{
			//przepisz bajt z buforu do stringu
			*(str++) = FIFO_Pop(&ble_RXbuf);
		}
		//kiedy Tail i Head juz sa rowne zakoncz string
		*str = '\0';
}
/*************************************************************************************************************/
/*Check frame control sum which always should be equal to 255*/
//uint8_t BLE_CheckControlSum(char* str)
//{
//	uint8_t tmp = 0;
//	while(*(str++) != '\0')
//		tmp+= *str;
//
//	if(tmp == 255) return 1;
//	else return 0;
//}
/*************************************************************************************************************/
