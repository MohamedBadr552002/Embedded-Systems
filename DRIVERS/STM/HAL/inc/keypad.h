/*
 * keypad.h
 *
 *  Created on: Feb 16, 2023
 *      Author: Mohamed
 */

#ifndef INCLUDES_KEYPAD_H_
#define INCLUDES_KEYPAD_H_

#include "stm32f103c6.h"
#include "STM32F103C6_DRIVER_GPIO.h"



#define KEYPAD_PORT				GPIOB


#define R0		GPIO_PIN0
#define R1		GPIO_PIN1
#define R2		GPIO_PIN3
#define R3		GPIO_PIN4

#define C0		GPIO_PIN5
#define C1		GPIO_PIN6
#define C2		GPIO_PIN7
#define C3		GPIO_PIN8

void KEYPAD_INIT(void );
char KEYPAD_GETCHAR(void );


#endif /* INCLUDES_KEYPAD_H_ */
