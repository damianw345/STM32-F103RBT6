#ifndef MAIN_H_
#define MAIN_H_

//STM32 libraries
#include "stm32f10x.h"

//INTERRUPTS configuration libraries
#include "_nvic_int_config.h"

//UTILS libraries
#include "gpio.h"
#include "terminal.h"
#include "SysTick.h"
#include "led.h"

//BLE libraries
#include "ble/fifo.h"
//#include "terminal.h"
#include "ble/interrupts.h"
#include "ble/ble.h"
#include "ble/typedefs.h"

//HCSR-04 libraries
#include "hc-sr04/config.h"
#include "hc-sr04/interrupt.h"
#include "hc-sr04/calculations.h"

//MLX90615 libraries
#include "mlx90615/smbus.h"
#include "mlx90615/mlx90615.h"

//MOTOR libraries
#include "dc_motor/tb6612.h"
#include "dc_motor/encoder.h"

//MAESTRO SERVO CONTROLLER libraries
#include "maestro_servo_controller/maestro.h"

//CNY-70 libraries
#include "cny70/config.h"

//extern volatile t_Flags transfer;  //to od BLE pliki
//extern volatile uint8_t counter;

#endif /* MAIN_H_ */
