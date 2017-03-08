/*
 * smbus.h
 *
 *  Created on: 8 gru 2016
 *      Author: samsung
 */

#ifndef SMBUS_H_
#define SMBUS_H_

#define SMBus_MY_ADDRESS       0x01
#define SMBus_NAME             I2C2
#define SMBus_RCC_Periph       RCC_APB1Periph_I2C2
#define SMBus_RCC_Port         RCC_APB2Periph_GPIOB
#define SMBus_Port             GPIOB
#define SMBus_SCL_Pin          GPIO_Pin_10
#define SMBus_SDA_Pin          GPIO_Pin_11
#define SMBus_Speed            100000


void Initialize_SMBus();
void smbusRead(I2C_TypeDef *I2Cx,uint8_t addr, uint8_t command, uint16_t* data);

#endif /* SMBUS_H_ */
