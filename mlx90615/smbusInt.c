///*
// * smbusInt.c
// *
// *  Created on: 13 gru 2016
// *      Author: samsung
// */
//
//#include "mlx90615/smbusInt.h"
//#include <stm32f10x_i2c.h>
//
////Choose which I2C to use in interrupt mode
////#define USE_I2C1
//#define USE_I2C2
//
//void Initialize_SMBusInt()
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//
//	/* Configure the I2C event priority */
//#ifdef USE_I2C1
//	NVIC_InitStructure.NVIC_IRQChannel                   = I2C1_EV_IRQn;
//#endif
//
//#ifdef USE_I2C2
//	NVIC_InitStructure.NVIC_IRQChannel                   = I2C2_EV_IRQn;
//#endif
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//
//#ifdef USE_I2C1
//	I2C_ITConfig(I2C1, I2C_IT_EVT , ENABLE);
//#endif
//
//#ifdef USE_I2C2
//	I2C_ITConfig(I2C2, I2C_IT_EVT , ENABLE);
//#endif
//}
//
//static volatile uint8_t cnt0 = 0;
//static volatile uint8_t cnt1 = 0;
//static volatile uint8_t cnt2 = 0;
//
//static volatile uint8_t lsb = 0;
//static volatile uint8_t msb = 0;
//volatile uint16_t data = 0;
//
//void I2C2_EV_IRQHandler(void)
//{
//    switch(I2C_GetLastEvent(I2C2))
//    {
//    //START za pierwszym razem nalezy wygenerowac poza funkcja
//    case I2C_EVENT_MASTER_MODE_SELECT:
//
//    	if(cnt0 == 0)//
//    	I2C_SendData(I2C2, 0xB6);//ADRES + WRite
//
//    	else if(cnt0 == 1)
//    	I2C_SendData(I2C2, 0xB7); //ADRES + ReaD
//
//    	cnt0++;
//    	if(cnt0>1) cnt1 = 0;
//    	I2C_ClearITPendingBit(I2C2,I2C_IT_EVT);
//        break;
//
//    case I2C_EVENT_MASTER_BYTE_TRANSMITTING:
//    	if(cnt1 == 0)
//    	{
//        I2C_AcknowledgeConfig(I2C2, ENABLE);
//        I2C_SendData(I2C2, 0x27); ///KOMENDA
//    	}
//
//    	else if(cnt1 == 1)
//    	{
//        	I2C_AcknowledgeConfig(I2C2, ENABLE);
//        	I2C_GenerateSTART(I2C2, ENABLE); //START2
//    	}
//
//    	cnt1++;
//    	if(cnt1>1) cnt1 = 0;
//    	I2C_ClearITPendingBit(I2C2,I2C_IT_EVT);
//    	break;
//
////    case I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED :
////        break;
//
//    case I2C_EVENT_MASTER_BYTE_RECEIVED:
//    	if(cnt2 ==0)//odbierz 1 bajt i nadaj ack
//    	{
//        I2C_AcknowledgeConfig(I2C2, ENABLE);
//        lsb = I2C_ReceiveData(I2C2); //PIERWSZY BAJT
//    	}
//
//    	else if(cnt2 ==1)//odbierz 2 bajt i nadaj ack
//    	{
//    		I2C_AcknowledgeConfig(I2C2, ENABLE);
//    		msb = I2C_ReceiveData(I2C2); //DRUGI BAJT
//    	}
//    	else if(cnt2 ==2)
//    	{
//    		I2C_AcknowledgeConfig(I2C2, DISABLE); //ZAKONCZ TRANSMISJE
//    		I2C_GenerateSTOP(I2C2, ENABLE);
//    	}
//    	else if(cnt2 ==3)
//    	{
//       	 data = ((uint16_t) msb << 8) | lsb;
////       	 I2C_GenerateSTART(I2C2, ENABLE);
//    	}
//    	cnt2++;
//    	if(cnt2>3)
//    		{
//    		cnt2 = 0;
//    		I2C_GenerateSTART(I2C2, ENABLE);//kolejny pomiar
//    		}
//    	I2C_ClearITPendingBit(I2C2,I2C_IT_EVT);
//        break;
//    }
//}
