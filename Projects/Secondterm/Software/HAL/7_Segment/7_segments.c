/*
 * 7_segments.c
 *
 *  Created on: Aug 23, 2023
 *      Author: Mohamed
 */

#include"7_segments.h"

uint16_t _7segment_num[]={ZERO , ONE, TWO, THREE, FOUR , FIVE, SIX, SEVEN, EIGHT, NINE};
GPIO_pinConfig_t *L_Config;


void HAL_7SEGMENT_INIT(void)
{
	L_Config ->GPIO_PIN_NUMBER = GPIO_PIN0;
	L_Config ->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	L_Config->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(GPIOA, L_Config);

	L_Config ->GPIO_PIN_NUMBER = GPIO_PIN1;
	L_Config ->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	L_Config->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(GPIOA, L_Config);

	L_Config ->GPIO_PIN_NUMBER = GPIO_PIN2;
	L_Config ->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	L_Config->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(GPIOA, L_Config);

	L_Config ->GPIO_PIN_NUMBER = GPIO_PIN3;
	L_Config ->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	L_Config->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(GPIOA, L_Config);

	L_Config ->GPIO_PIN_NUMBER = GPIO_PIN4;
	L_Config ->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	L_Config->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(GPIOA, L_Config);

	L_Config ->GPIO_PIN_NUMBER = GPIO_PIN5;
	L_Config ->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	L_Config->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(GPIOA, L_Config);

	L_Config ->GPIO_PIN_NUMBER = GPIO_PIN6;
	L_Config ->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	L_Config->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(GPIOA, L_Config);


}



void HAL_7SEGMENT_OUT(GPIO_typeDef* gpiox ,uint16_t NUM )
{
	//MCAL_GPIO_WriteGroup(gpiox, NUM, 0x0F);
	MCAL_GPIO_Writeport(gpiox, NUM);
}
