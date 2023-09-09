/*
 * STM32F103C6_DRIVER_RCC.c
 *
 *  Created on: Mar 17, 2023
 *      Author: Mohamed
 */

#include "STM32F103C6_DRIVER_RCC.h"

const APBPrescTable[8U] = {0,0,0,0,1,2,3,4};

const AHBPrescTable[16U] = {0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8};

uint32_t MCAL_RCC_GET_SYSCLK_Freq(void)
{

	switch((RCC->CFGR >> 2)& 0b11)
	{
		case 0 :
			return HSI_RC_CLK ;
			break;
		case 1 :
			//not calculated yet
			return HSE_CLK ;
			break;
		case 2 :
			//not calculated yet
			return 1600000 ;
			break;
	}
}
uint32_t	MCAL_RCC_GET_HCLK_Freq(void)
{
	//Read the freq from HCLK to know the Freq os PCLK2
	return (MCAL_RCC_GET_SYSCLK_Freq() >> AHBPrescTable[(RCC->CFGR>>4) & 0xF ]);
}
uint32_t MCAL_RCC_GET_PCLK1_Freq(void)
{
	//Read the freq from HCLK to know the Freq of PCLK1
	return (MCAL_RCC_GET_HCLK_Freq() >> APBPrescTable[(RCC->CFGR>>8) & 0b111 ]);
}
uint32_t MCAL_RCC_GET_PCLK2_Freq(void)
{
	//Read the freq from HCLK to know the Freq of PCLK2
	return (MCAL_RCC_GET_HCLK_Freq() >> APBPrescTable[(RCC->CFGR>>11) & 0b111 ]);
}
