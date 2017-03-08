/*
 * pid.h
 *
 *  Created on: 20 paü 2016
 *      Author: samsung
 */

#ifndef PID_H_
#define PID_H_
#include "stm32f10x.h"

uint16_t PID(uint16_t req_speed, uint16_t measured_speed);

#endif /* PID_H_ */
