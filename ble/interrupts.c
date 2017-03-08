/*
 * interrupts.c
 *
 *  Created on: 7 paŸ 2016
 *      Author: samsung
 */

#include "ble/interrupts.h"
#include "ble/typedefs.h"

extern FIFO_type ble_RXbuf;
extern FIFO_type ble_TXbuf;

t_Flags transfer = incomplete;
t_boolean frameStart = false;

volatile uint8_t counter=0;

/*************************************************************************************************************/
//void NVIC_Configuration()
//{
//  NVIC_InitTypeDef NVIC_InitStructure;
//
//  /* Ustawienie grupy priorytetów */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//
//  /* Uruchomienie przerwania od USART2 */
//  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 16;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
//}
/*************************************************************************************************************/

void USART2_IRQHandler(void)
{
  uint16_t tmp;
  //RX interrupt
  if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
  {
      USART_ClearITPendingBit(USART2,USART_IT_RXNE);
      tmp=USART_ReceiveData(USART2);
      if(tmp == '!')
    	  frameStart = true;
      FIFO_Put(&ble_RXbuf,(uint8_t)(tmp%256));

      //beginning of frame is '!'
      if(frameStart == true)
      {
          //count until frame will be received
          counter++;
          	  if(counter== WORD_LENGTH)
          	  {
          		counter = 0;
          		transfer = complete;
          		frameStart = false;
          	  }
      }
      //else - leci cos innego niz komenda - zapisze sie w RXbufie wiec jak trzeba mozna sprawdzic
  }

  //TX interrupt
  if(USART_GetITStatus(USART2,USART_IT_TXE) != RESET)
  {
      USART_ClearITPendingBit(USART2,USART_IT_TXE);
      if(FIFO_IsEmpty(&ble_TXbuf))
        USART_ITConfig(USART2,USART_IT_TXE,DISABLE);
      else
        USART_SendData(USART2,(uint16_t)FIFO_Pop(&ble_TXbuf));
  }
}
/*************************************************************************************************************/
/*send string via USART with interrupts*/
void USART_print(char* str)
{
  int index=0;
  while(str[index]!='\0')
    FIFO_Put(&ble_TXbuf,str[index++]);
  USART_ITConfig(USART2,USART_IT_TXE,ENABLE);
}
/*************************************************************************************************************/

