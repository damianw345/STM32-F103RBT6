/*
 * terminal.c
 *
 * Example initialization
 *
 * Initialize_USART_RCC();
 * Initialize_USART(USART2);
 *
 */

#include "terminal.h"

/*Configure which USARTs should be used*/
#define USE_UART1
#define USE_UART2
//#define USE_UART3

/*Configure which USARTs should use interrupts*/
//#define USE_INT1
#define USE_INT2
//#define USE_INT3

/*Configure which USARTs should use DMA*/
//#define USE_DMA1
//#define USE_DMA2
//#define USE_DMA3

void Initialize_UART(void)
{
/*************************************************************************************************************/
	/*Initialize USARTs RCCs*/
	#ifdef USE_UART1
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//uncomment if not turned on earlier
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	#endif

	#ifdef 	USE_UART2
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	#endif

	#ifdef 	USE_UART3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	#endif
/*************************************************************************************************************/

	/*Initialize GPIO for USART*/
	GPIO_InitTypeDef gpio;
	GPIO_StructInit(&gpio);

	#ifdef USE_UART1
	//TX LINE
	gpio.GPIO_Pin = GPIO_Pin_9;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
 	GPIO_Init(GPIOA, &gpio);

 	 //RX LINE
 	 gpio.GPIO_Pin = GPIO_Pin_10;
 	 gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 	 GPIO_Init(GPIOA, &gpio);

	 //USARTx configuration
	USART_InitTypeDef uart;
	USART_StructInit(&uart);
	uart.USART_BaudRate = 115385;///////////////////////////////////////////////////////
	USART_Init(USART1, &uart);
	USART_Cmd(USART1, ENABLE);

		#ifdef USE_INT1
		//Uruchomienie przerwania od USART1
		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
		USART_ITConfig(USART1,USART_IT_TXE,ENABLE);
		#endif

	#endif

	#ifdef USE_UART2
	 //TX LINE
	 gpio.GPIO_Pin = GPIO_Pin_2;
	 gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	 GPIO_Init(GPIOA, &gpio);

	 //RX LINE
	 gpio.GPIO_Pin = GPIO_Pin_3;
	 gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	 GPIO_Init(GPIOA, &gpio);

	 //USARTx configuration
	USART_InitTypeDef uart2;
	USART_StructInit(&uart2);
	uart2.USART_BaudRate = 115200;
	USART_Init(USART2, &uart2);
	USART_Cmd(USART2, ENABLE);

		#ifdef USE_INT2
		//Uruchomienie przerwania od USART2
		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
		USART_ITConfig(USART2,USART_IT_TXE,ENABLE);
		#endif
	#endif

	 #ifdef USE_UART3
	 //TX LINE
	 gpio.GPIO_Pin = GPIO_Pin_10;
	 gpio.GPIO_Mode = GPIO_Mode_AF_PP;
 	 GPIO_Init(GPIOB, &gpio);

 	 //RX LINE
 	 gpio.GPIO_Pin = GPIO_Pin_11;
 	 gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 	 GPIO_Init(GPIOB, &gpio);

	 //USARTx configuration
	USART_InitTypeDef uart;
	USART_StructInit(&uart);
	uart.USART_BaudRate = 115200;
	USART_Init(USART3, &uart);
	USART_Cmd(USART3, ENABLE);

		#ifdef USE_INT3
		//Uruchomienie przerwania od USART3
		USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
		USART_ITConfig(USART3,USART_IT_TXE,ENABLE);
		#endif

	 #endif

/*************************************************************************************************************/
// NOT TESTED
//	#ifdef USE_DMA
//	  USART_DMACmd(USART1, USART_DMAReq_Tx | USART_DMAReq_Rx, ENABLE);
//	#endif
/*************************************************************************************************************/
}

/*use to send single byte without interrupts*/
void UART_SendChar(USART_TypeDef * USARTx, char c)
{
while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
USART_SendData(USARTx, c);
}

/*use to send string without interrupts*/
void UART_SendString(USART_TypeDef * USARTx, char* s)
{
	while(*s)
		UART_SendChar(USARTx,*s++);
}

/*get char from the UART Data Register without interrupts*/
char UART_GetChar(USART_TypeDef * USARTx)
{
	char data;
		//czekaj az bufor odbiorczy bedzie pusty
		while(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);
	data = USART_ReceiveData(USARTx);
	return data;
}

//uncomment to use printf() and in terminal.h uncomment #include <stdio.h>
//useful when debugging
//int __io_putchar(int c)
//{
//if (c=='\n')
//
////#ifdef USE_UART1
////send_char(USART1,'\r');
////send_char(USART1,c);
////#endif
//
//#ifdef USE_UART2
//send_char(USART2,'\r');
//send_char(USART2,c);
//#endif
//
////#ifdef USE_UART3
////send_char(USART3,'\r');
////send_char(USART3,c);
////#endif
//
//return c;
//}
