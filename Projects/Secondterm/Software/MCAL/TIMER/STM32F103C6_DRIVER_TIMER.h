/*
 * STM32F103C6_DRIVER_TIMER.h
 *
 *  Created on: Aug 27, 2023
 *      Author: Mohamed
 */

#ifndef INC_STM32F103C6_DRIVER_TIMER_H_
#define INC_STM32F103C6_DRIVER_TIMER_H_

#include "stm32f103c6.h"
#include "STM32F103C6_DRIVER_GPIO.h"


#define RCC_APB1ENR                           *( volatile uint32_t *)(RCC_BASE+0x1C)
#define RCC_APB2ENR                           *( volatile uint32_t *)(RCC_BASE+0x18)





//TIMER2
#define TIM2_timer_Base                        0x40000000
#define TIM2_CNT                              *( volatile uint32_t *)(TIM2_timer_Base+0x24)
#define TIM2_CR1                              *( volatile uint32_t *)(TIM2_timer_Base+0x00)
#define TIM2_PSC                              *( volatile uint32_t *)(TIM2_timer_Base+0x28)
#define TIM2_SR                               *( volatile uint32_t *)(TIM2_timer_Base+0x10)
#define TIM2_DIER                             *( volatile uint32_t *)(TIM2_timer_Base+0x0c)
#define TIM2_ARR                              *( volatile uint32_t *)(TIM2_timer_Base+0x2c)
#define RCC_APB1ENR                           *( volatile uint32_t *)(RCC_BASE+0x1C)



/*=================Timer2======================*/
void MCAL_Timer2_init(void);
void dus(int us);
void dms(int ms);


#endif /* INC_STM32F103C6_DRIVER_TIMER_H_ */
