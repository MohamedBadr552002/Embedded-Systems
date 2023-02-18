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

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "stm32f103c6.h"
#include "STM32F103C6_DRIVER_GPIO.h"
#include "keybad.h"
#include "LCD.h"
#include "STM32F103C6_DRIVER_EXTI.h"

uint8_t  IQR_FLAG=0 ;

void CLOCK_INIT(void)
{
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();

	RCC_AFIO_CLK_EN();

}


void delay(int x)
{
	unsigned int i,j;

	for (i=0 ; i<x ;i++)
	{
		for (j=0 ;j<255;j++);
	}
}


void EXTI9callback()
{
	IQR_FLAG =1 ;
	LCD_WRITE_STRING("RAISING TRIGGER");
	delay(1000);

}

int main(void)
{

	CLOCK_INIT();
	LCD_INIT();
	KEYBAD_INIT() ;
	LCD_WRITE_STRING("HI there ...");
	delay(500);
	LCD_clear_screen();



	EXTI_Pinconfig_t EXTI_CFG ;

	EXTI_CFG.EXTI_PIN = EXTI9PB9 ;
	EXTI_CFG.Trigger_Case =EXTI_TRIGGER_RAISING ;
	EXTI_CFG.IRQ_EN   = EXTI_IRQ_ENABLE ;
	EXTI_CFG.P_IRQ_CallBack = EXTI9callback;


	MCAL_EXTI_INIT(&EXTI_CFG);



	IQR_FLAG = 1;
	while (1)
	{
		if (IQR_FLAG )
		{
			LCD_clear_screen();
			IQR_FLAG = 0 ;
		}

	}
}
