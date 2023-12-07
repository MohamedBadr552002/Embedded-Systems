/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mohamed Badr
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
#include "core_cm3.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif



#include "stm32f103c6.h"
#include "STM32F103C6_DRIVER_GPIO.h"
#include "keybad.h"
#include "LCD.h"
#include "7_segments.h"
#include "I2C_slave_EEPROM.h"
#include "Servo_Motor.h"
#include "STM32F103C6_DRIVER_EXTI.h"
#include "STM32F103C6_DRIVER_RCC.h"
#include "STM32F103C6_DRIVER_USART.h"
#include "STM32F103C6_DRIVER_SPI.h"
#include "STM32F103C6_DRIVER_I2C.h"
#include "STM32F103C6_DRIVER_TIMER.h"
#include "scheduler.h"




int main()
{
	RTOS_State_ID rtos_state;
	HardWare_INIT();

	rtos_state = RTOS_INIT();

    while(1)
    {
    		//task11111

    }
}













