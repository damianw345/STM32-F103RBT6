/*
 * smbus.c
 *
 *  Created on: 8 gru 2016
 *      Author: samsung
 */
#include <stm32f10x_i2c.h>
#include "mlx90615/smbus.h"

void Initialize_SMBus()
{
    I2C_InitTypeDef SMBus;
    GPIO_InitTypeDef gpio;

    /* Enable I2C and GPIO clocks */
    RCC_APB1PeriphClockCmd(SMBus_RCC_Periph, ENABLE);
    RCC_APB2PeriphClockCmd(SMBus_RCC_Port, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

    /* Configure SMBus pins: SCL and SDA */
    gpio.GPIO_Pin = SMBus_SCL_Pin | SMBus_SDA_Pin;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(SMBus_Port, &gpio);


    /* SMBus configuration */
    I2C_StructInit(&SMBus);
    SMBus.I2C_Mode = I2C_Mode_SMBusHost;
    SMBus.I2C_DutyCycle = I2C_DutyCycle_2;
    SMBus.I2C_OwnAddress1 = SMBus_MY_ADDRESS;
    SMBus.I2C_Ack = I2C_Ack_Enable;
    SMBus.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    SMBus.I2C_ClockSpeed = SMBus_Speed;

    /* Apply SMBus configuration after enabling it */
    I2C_Init(SMBus_NAME, &SMBus);
    I2C_Cmd(SMBus_NAME, ENABLE);
}

void smbusRead(I2C_TypeDef *I2Cx,uint8_t addr, uint8_t command, uint16_t* data)
{
	uint16_t counter = 10000;

	uint8_t buff[2];
	I2C_GenerateSTART(I2Cx, ENABLE); //START1
	while ( (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS) && counter)
		counter--;

	counter = 10000;
	I2C_SendData(I2Cx,addr<<1);//ADRES + WRite
	while ( (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS)&& counter)
		counter--;

	I2C_AcknowledgeConfig(I2Cx, ENABLE);

	counter = 10000;
	I2C_SendData(I2Cx, command); ///KOMENDA
	while ( (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS)&& counter)
		counter--;

	I2C_AcknowledgeConfig(I2Cx, ENABLE);

	counter = 10000;
	I2C_GenerateSTART(I2Cx, ENABLE); //START2
	while ( (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)&& counter)
		counter--;

	counter = 10000;
	I2C_SendData(I2Cx, (addr<<1)|0x01); //ADRES + ReaD
	while ( (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)!= SUCCESS)&& counter)
		counter--;

	counter = 10000;
	while ( (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)!=SUCCESS)&& counter)//odbierz ACK
		counter--;

	I2C_AcknowledgeConfig(I2Cx, ENABLE);

	counter = 10000;
	buff[0] = I2C_ReceiveData(I2Cx); //PIERWSZY BAJT
	while ( (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)!=SUCCESS)&& counter)
		counter--;

	I2C_AcknowledgeConfig(I2Cx, ENABLE);

	counter = 10000;
	buff[1] = I2C_ReceiveData(I2Cx); //DRUGI BAJT
	while ( (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)!=SUCCESS)&& counter)
		counter--;

	counter = 10000;
	I2C_AcknowledgeConfig(I2Cx, DISABLE); //ZAKONCZ TRANSMISJE
	I2C_GenerateSTOP(I2Cx, ENABLE);
	while ( (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS)&& counter)
		counter--;

	*data = ((uint16_t) buff[1] << 8) | buff[0];
}

//NIE TESTOWANE !!!!
void smbusWrite(I2C_TypeDef *I2Cx,uint8_t addr, uint8_t command, uint16_t data)
{
	uint8_t buff[2] = {0};

	buff[0] = data<<8;//data byte low
	buff[1] = data>>8;//data byte high

	I2C_GenerateSTART(I2Cx, ENABLE); //START1
	while (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
		;

	I2C_SendData(I2Cx,addr<<1);//ADRES + WRite
	while (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS)
		;

	I2C_AcknowledgeConfig(I2Cx, ENABLE);

	I2C_SendData(I2Cx, command); ///KOMENDA
	while (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS)
		;

	I2C_AcknowledgeConfig(I2Cx, ENABLE);

	I2C_SendData(I2Cx, buff[0]); //DATA BYTE LOW
	while (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS)
		;

	I2C_AcknowledgeConfig(I2Cx, ENABLE);

	I2C_SendData(I2Cx, buff[1]); //DATA BYTE HIGH
	while (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS)
		;

	I2C_AcknowledgeConfig(I2Cx, DISABLE); //ZAKONCZ TRANSMISJE
	I2C_GenerateSTOP(I2Cx, ENABLE);
	while (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS)
		;
}


///**
// * Calculate CRC8 sum for a word
// * @param data input word
// * @return calculated CRC8 for an input word
// */
//uint8_t SMBus_CRC8(uint32_t data)
//{
//	uint32_t msg = data << 8;
//	uint32_t key = 0x107 << 23;
//	uint32_t mask = 1 << 31;
//	while(mask > 0x80) {
//		if(mask & msg) {
//			msg ^= key;
//		}
//		key >>= 1;
//		mask >>= 1;
//	}
//	return msg;
//}
