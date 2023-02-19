/*
 * stm32f103c6.h
 *
 *  Created on: Feb 16, 2023
 *      Author: Mohamed
 */

#ifndef INC_STM32F103C6_H_
#define INC_STM32F103C6_H_

//-----------------------------
//Includes
//-----------------------------
#include "stdlib.h"
#include "stdint.h"

//-----------------------------
//Base addresses for Memories
//-----------------------------
#define FLASH_MEMORY_BASE    						0x08000000UL
#define SYSTEM_MEMORY_BASE							0x1FFFF000UL
#define SRAM_MEMORY_BASE 							0x20000000UL

#define PERIPHERALS_BASE 							0x40000000UL
#define CORTEX_M3_INTERNAL_PERIPHERALS_BASE    	    0xE0000000UL
#define NVIC_BASE									0xE000E100UL

#define NVIC_ISER0									*(volatile uint32_t *)(NVIC_BASE + 0x0)
#define NVIC_ISER1									*(volatile uint32_t *)(NVIC_BASE + 0x4)
#define NVIC_ISER2									*(volatile uint32_t *)(NVIC_BASE + 0x8)
#define NVIC_ICER0									*(volatile uint32_t *)(NVIC_BASE + 0x80)
#define NVIC_ICER1									*(volatile uint32_t *)(NVIC_BASE + 0x84)
#define NVIC_ICER2									*(volatile uint32_t *)(NVIC_BASE + 0x88)


//-----------------------------
//Base addresses for AHP BUS Peripherals
//-----------------------------
        //RCC
#define RCC_BASE  							    0x40021000UL

//-----------------------------
//Base addresses for APB2 BUS Peripherals
//-----------------------------
            //GPIO
//A,B FULLY included in LQFP48 package
#define GPIOA_BASE   						    0x40010800UL
#define GPIOB_BASE   						    0x40010C00UL

//C,D Partial included in LQFP48 package
#define GPIOC_BASE                              0x40011000UL
#define GPIOD_BASE                              0x40011400UL

//E not included in LQFP48 package
#define GPIOE_BASE                              0x40011800UL

		  //EXTI
#define EXTI_BASE  							    0x40010400UL

		 //AFIO
#define AFIO_BASE  							    0x40010000UL
//-----------------------------
//Base addresses for APB1 BUS Peripherals
//-----------------------------


//==================================================================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:GPIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct {
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_typeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct {
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
}RCC_typeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct {
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_typeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct {
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4];
	uint32_t reserved0;
	volatile uint32_t MAPR2;
}AFIO_typeDef;

//=========================================================================================
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA      ((GPIO_typeDef *)GPIOA_BASE)
#define GPIOB      ((GPIO_typeDef *)GPIOB_BASE)
#define GPIOC      ((GPIO_typeDef *)GPIOC_BASE)
#define GPIOD      ((GPIO_typeDef *)GPIOD_BASE)
#define GPIOE      ((GPIO_typeDef *)GPIOE_BASE)

#define RCC        ((RCC_typeDef  *)RCC_BASE)

#define AFIO       ((AFIO_typeDef *)AFIO_BASE)

#define EXTI       ((EXTI_typeDef *)EXTI_BASE)

//==============================================================================================
//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define RCC_GPIOA_CLK_EN()   (RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLK_EN()   (RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLK_EN()   (RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_CLK_EN()   (RCC->APB2ENR |= 1<<5)
#define RCC_GPIOE_CLK_EN()   (RCC->APB2ENR |= 1<<6)

#define RCC_AFIO_CLK_EN()    (RCC->APB2ENR |= 1<<0 )

//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC IRQ enable & disable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

//#define NVIC_LINE_ENABLE					1
//#define	NVIC_LINE_DISABLE					0

#define NVIC_IRQ6_EXTI0_Enable 							(NVIC_ISER0	|= 1<<6)
#define NVIC_IRQ7_EXTI1_Enable 							(NVIC_ISER0	|= 1<<7)
#define NVIC_IRQ8_EXTI2_Enable 							(NVIC_ISER0	|= 1<<8)
#define NVIC_IRQ9_EXTI3_Enable 							(NVIC_ISER0	|= 1<<9)
#define NVIC_IRQ10_EXTI4_Enable 						(NVIC_ISER0	|= 1<<10)
#define NVIC_IRQ23_EXTI5_9_Enable 						(NVIC_ISER0	|= 1<<23)
#define NVIC_IRQ40_EXTI10_15_Enable 					(NVIC_ISER0	|= 1<<8) // 40 - 32 = 8

#define NVIC_IRQ6_EXTI0_Disable 						(NVIC_ICER0	|= 1<<6)
#define NVIC_IRQ7_EXTI1_Disable 						(NVIC_ICER0	|= 1<<7)
#define NVIC_IRQ8_EXTI2_Disable 						(NVIC_ICER0	|= 1<<8)
#define NVIC_IRQ9_EXTI3_Disable 						(NVIC_ICER0	|= 1<<9)
#define NVIC_IRQ10_EXTI4_Disable 						(NVIC_ICER0	|= 1<<10)
#define NVIC_IRQ23_EXTI5_9_Disable 						(NVIC_ICER0	|= 1<<23)
#define NVIC_IRQ40_EXTI10_15_Disable 					(NVIC_ICER1	|= 1<<8) // 40 - 32 = 8)



//-*-*-*-*-*-*-*-*-*-*-*-
//IVT
//-*-*-*-*-*-*-*-*-*-*-*
//EXTI





// Interrupt request line Number
#define 	EXTI0_IRQ			6
#define 	EXTI1_IRQ			7
#define 	EXTI2_IRQ			8
#define 	EXTI3_IRQ			9
#define 	EXTI4_IRQ			10
#define 	EXTI5_IRQ			23
#define 	EXTI6_IRQ			23
#define 	EXTI7_IRQ			23
#define 	EXTI8_IRQ			23
#define 	EXTI9_IRQ			23
#define 	EXTI10_IRQ			40
#define 	EXTI11_IRQ			40
#define 	EXTI12_IRQ			40
#define 	EXTI13_IRQ			40
#define 	EXTI14_IRQ			40
#define 	EXTI15_IRQ			40




#endif /* INC_STM32F103C6_H_ */

