/*
 * Servo_Motor.h
 *
 *  Created on: Aug 27, 2023
 *      Author: Mohamed
 */

#ifndef INCLUDES_SERVO_MOTOR_H_
#define INCLUDES_SERVO_MOTOR_H_

#include "stm32f103c6.h"
#include "STM32F103C6_DRIVER_GPIO.h"
#include "STM32F103C6_DRIVER_TIMER.h"


void HAL_Servo1_Entry_Gate_Init(void);
void HAL_Servo1_Entry_Gate(uint8_t Direction);

void HAL_Servo2_Exit_Gate_Init(void);
void HAL_Servo2_Exit_Gate(uint8_t Direction);



#endif /* INCLUDES_SERVO_MOTOR_H_ */
