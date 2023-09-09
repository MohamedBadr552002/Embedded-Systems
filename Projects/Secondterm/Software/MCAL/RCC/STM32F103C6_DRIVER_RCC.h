/*
 * STM32F103C6_DRIVER_RCC.h
 *
 *  Created on: Mar 17, 2023
 *      Author: Mohamed
 */

#ifndef INC_STM32F103C6_DRIVER_RCC_H_
#define INC_STM32F103C6_DRIVER_RCC_H_

#include "stm32f103c6.h"



#define HSI_RC_CLK		(uint32_t)8000000
#define	HSE_CLK			(uint32_t)16000000

uint32_t MCAL_RCC_GET_SYSCLK_Freq(void);
uint32_t	MCAL_RCC_GET_HCLK_Freq(void);	// HCLK is the clock which input to AHB BUS
uint32_t MCAL_RCC_GET_PCLK1_Freq(void); // PCLK1 is the clock which input to APB1 BUS
uint32_t MCAL_RCC_GET_PCLK2_Freq(void); // PCLK2 is the clock which input to APB2 BUS






#endif /* INC_STM32F103C6_DRIVER_RCC_H_ */
