
#ifndef BLE_H_
#define BLE_H_

#include "stm32f10x.h"
#include "typedefs.h"

#define BUTTON_1 '1'
#define BUTTON_2 '2'
#define BUTTON_3 '3'
#define BUTTON_4 '4'
#define ARROW_UP '5'
#define ARROW_DOWN '6'
#define ARROW_LEFT '7'
#define ARROW_RIGHT '8'

char ble_commandBuf[WORD_LENGTH];

void BLE_switchCommand();
void BLE_readRXbuf(char* str);
void BLE_executeIfTransferIsComplete();
//uint8_t BLE_CheckControlSum(char* str);

#endif /* BLE_H_ */
