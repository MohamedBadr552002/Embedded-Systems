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



void CLOCK_INIT(void)
{
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();

}


void wait_ms(uint32_t time)
{
	uint32_t i,j;
	for(i=0;i<time;i++)
		for(j=0;j<255;j++);
}



int main(void)
{

	CLOCK_INIT();

	GPIO_pinConfig_t *GPIO_GFC ;

	GPIO_GFC->GPIO_PIN_NUMBER = GPIO_PIN1;
	GPIO_GFC->GPIO_MODE=GPIO_MODE_OUTPUT_OD;
	GPIO_GFC->GPIO_OUTPUT_SPEED =GPIO_SPEED_10M ;
	MCAL_GPIO_Init(GPIOB, GPIO_GFC);

	GPIO_GFC->GPIO_PIN_NUMBER = GPIO_PIN13;
	GPIO_GFC->GPIO_MODE=GPIO_MODE_OUTPUT_OD;
	GPIO_GFC->GPIO_OUTPUT_SPEED =GPIO_SPEED_10M ;
	MCAL_GPIO_Init(GPIOB, GPIO_GFC);


	GPIO_GFC->GPIO_PIN_NUMBER = GPIO_PIN5;
	GPIO_GFC->GPIO_MODE=GPIO_MODE_OUTPUT_OD;
	GPIO_GFC->GPIO_OUTPUT_SPEED =GPIO_SPEED_10M ;
	MCAL_GPIO_Init(GPIOB, GPIO_GFC);

	GPIO_GFC->GPIO_PIN_NUMBER = GPIO_PIN1 ;
	GPIO_GFC->GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA,GPIO_GFC);



	while (1)
	{
		MCAL_GPIO_Writepin(GPIOB, GPIO_PIN1, GPIO_PIN_SET);
		MCAL_GPIO_Writepin(GPIOB, GPIO_PIN13, GPIO_PIN_SET);
		MCAL_GPIO_Writepin(GPIOB, GPIO_PIN5, GPIO_PIN_SET);

		if( MCAL_GPIO_Readpin(GPIOA, GPIO_PIN1) == 0)
		{
			MCAL_GPIO_Writepin(GPIOB, GPIO_PIN1, GPIO_PIN_RESET);
			wait_ms(500);
			MCAL_GPIO_Writepin(GPIOB, GPIO_PIN1, GPIO_PIN_SET);
			wait_ms(500);
			MCAL_GPIO_Writepin(GPIOB, GPIO_PIN13, GPIO_PIN_RESET);
			wait_ms(500);
			MCAL_GPIO_Writepin(GPIOB, GPIO_PIN13, GPIO_PIN_SET);
			wait_ms(500);
			MCAL_GPIO_Writepin(GPIOB, GPIO_PIN5, GPIO_PIN_RESET);
			wait_ms(500);
			MCAL_GPIO_Writepin(GPIOB, GPIO_PIN5, GPIO_PIN_SET);

		}

	}
}
