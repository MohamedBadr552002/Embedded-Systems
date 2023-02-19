/*
 * STM32F103C6_DRIVER_EXTI.c
 *
 *  Created on: Feb 16, 2023
 *      Author: Mohamed
 */


#include "STM32F103C6_DRIVER_EXTI.h"


//-----------------------------
//Generic Variables
//-----------------------------

void (*GP_IRQ_CallBack[15])(void);


//-----------------------------
//Generic Macros
//-----------------------------

#define  AFIO_GPIO_EXTI_Mapping(x)			(		(x == GPIOA)?0:\
													(x == GPIOB)?1:\
													(x == GPIOC)?2:\
													(x == GPIOD)?3:0		)
//-----------------------------
//Generic Function
//-----------------------------


void NVIC_CONTROL_ENABLE(uint16_t IRQ )
{


		switch(IRQ)
		{
			case 0 :
				NVIC_IRQ6_EXTI0_Enable;
				break;
			case 1 :
				NVIC_IRQ7_EXTI1_Enable;
				break;
			case 2 :
				NVIC_IRQ8_EXTI2_Enable;
				break;
			case 3 :
				NVIC_IRQ9_EXTI3_Enable;
				break;
			case 4 :
				NVIC_IRQ10_EXTI4_Enable;
				break;
			case 5 :
			case 6 :
			case 7 :
			case 8 :
			case 9 :
				NVIC_IRQ23_EXTI5_9_Enable;
				break;
			case 10 :
			case 11 :
			case 12 :
			case 13 :
			case 14 :
			case 15 :
				NVIC_IRQ40_EXTI10_15_Enable;
				break;

		}



}


void NVIC_CONTROL_DISABLE(uint16_t IRQ )
{
	switch(IRQ)
	{
	case 0 :
		NVIC_IRQ6_EXTI0_Disable;
		break;
	case 1 :
		NVIC_IRQ7_EXTI1_Disable;
		break;
	case 2 :
		NVIC_IRQ8_EXTI2_Disable;
		break;
	case 3 :
		NVIC_IRQ9_EXTI3_Disable;
		break;
	case 4 :
		NVIC_IRQ10_EXTI4_Disable;
		break;
	case 5 :
	case 6 :
	case 7 :
	case 8 :
	case 9 :
		NVIC_IRQ23_EXTI5_9_Disable;
		break;
	case 10 :
	case 11 :
	case 12 :
	case 13 :
	case 14 :
	case 15 :
		NVIC_IRQ40_EXTI10_15_Disable;
		break;

	}

}


void UPDATE_EXTI(EXTI_Pinconfig_t * EXTI_Config)
{

	//1- configure GPIO to be AF Input -> Floationg Input
	GPIO_pinConfig_t pincf;
	pincf.GPIO_PIN_NUMBER  =  EXTI_Config->EXTI_PIN.GPIO_PIN ;
	pincf.GPIO_MODE		   =  GPIO_MODE_INPUT_FLO	;
	MCAL_GPIO_Init(EXTI_Config->EXTI_PIN.GPIO_PORT, &pincf);

	//2- Updata AFIO to rotate GPIO With port A,B,C,D

	uint8_t  AFIO_EXTICR_Index		= 	EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER / 4 ;
	uint8_t	 AFIO_EXTICR_Position	=	(EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER % 4 ) * 4 ;
	//clear 4 bit
	AFIO->EXTICR[AFIO_EXTICR_Index] &= ~(0xF << AFIO_EXTICR_Position) ;
	AFIO->EXTICR[AFIO_EXTICR_Index] |= ((AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_PORT) & 0xF) << AFIO_EXTICR_Position );

	//3- update Raising or Falling edge
	EXTI->RTSR &= ~(1<<EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER);
	EXTI->FTSR &= ~(1<<EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER);

	if(EXTI_Config->Trigger_Case == EXTI_TRIGGER_RAISING)
	{
		EXTI->RTSR |= (1<<EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER);
	}
	else if (EXTI_Config->Trigger_Case == EXTI_TRIGGER_FALLING)
	{
		EXTI->FTSR |= (1<<EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER);
	}
	else if (EXTI_Config->Trigger_Case == EXTI_TRIGGER_raisingANDfalling)
	{
		EXTI->RTSR |= (1<<EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER);
		EXTI->FTSR |= (1<<EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER);
	}

	//4- update IRQ Handler callback
	GP_IRQ_CallBack[EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER] = EXTI_Config->P_IRQ_CallBack ;

	//5- Enable /Disable IRQ EXTI & NVIC
	if(EXTI_Config->IRQ_EN == EXTI_IRQ_ENABLE)
	{
		EXTI->IMR |=  (1<< EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER);
		NVIC_CONTROL_ENABLE(EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER );
	}
	else
	{
		EXTI->IMR &= ~(1<< EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER);
		NVIC_CONTROL_DISABLE(EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER );
	}


}


/**================================================================
* @Fn				-MCAL_EXTI_INIT
* @brief		    -Initialize EXTI for specific GPIO PIN and spaecify the Mask/ trigger condition and IRQ CallBack
* @param [in] 		-EXTI_Config
* @retval		    -none
* Note				-none
*
*/

void MCAL_EXTI_INIT	(EXTI_Pinconfig_t* EXTI_Config)
{
	UPDATE_EXTI(EXTI_Config);

}

void MCAL_EXTI_UPDATE(EXTI_Pinconfig_t* EXTI_Config)
{
	UPDATE_EXTI(EXTI_Config);
}

/**================================================================
* @Fn				-MCAL_EXTI_DEINIT
* @brief		    -RESET EXTI Register and NVIC
* @param [in] 		-none
* @retval		    -none
* Note				-none
*
*/

void MCAL_EXTI_DEINIT(void)
{
	EXTI->IMR 	= 0x00000000 ;
	EXTI->EMR 	= 0x00000000 ;
	EXTI->RTSR 	= 0x00000000 ;
	EXTI->FTSR 	= 0x00000000 ;
	EXTI->SWIER = 0x00000000 ;

	EXTI->PR 	= 0xFFFFFFFF ; //write one to clear

	 NVIC_IRQ6_EXTI0_Disable;
	 NVIC_IRQ7_EXTI1_Disable;
	 NVIC_IRQ8_EXTI2_Disable;
	 NVIC_IRQ9_EXTI3_Disable;
	 NVIC_IRQ10_EXTI4_Disable;
	 NVIC_IRQ23_EXTI5_9_Disable;
     NVIC_IRQ40_EXTI10_15_Disable;


}


//-----------------------------
//ISR
//-----------------------------

void EXTI0_IRQHandler(void)
{
	//clear interrupt by writing 1 on pending register EXTI_PR
	EXTI->PR |= 1<<0 ;
	//Call   IRQcallback
	GP_IRQ_CallBack[0]();

}

void EXTI1_IRQHandler(void)
{
	//clear interrupt by writing 1 on pending register EXTI_PR
	EXTI->PR |= 1<<1 ;
	//Call   IRQcallback
	GP_IRQ_CallBack[1]() ;

}

void EXTI2_IRQHandler(void)
{
	//clear interrupt by writing 1 on pending register EXTI_PR
	EXTI->PR |= 1<<2 ;
	//Call   IRQcallback
	GP_IRQ_CallBack[2]() ;

}

void EXTI3_IRQHandler(void)
{
	//clear interrupt by writing 1 on pending register EXTI_PR
	EXTI->PR |= 1<<3 ;
	//Call   IRQcallback
	GP_IRQ_CallBack[3]() ;

}

void EXTI4_IRQHandler(void)
{
	//clear interrupt by writing 1 on pending register EXTI_PR
	EXTI->PR |= 1<<4 ;
	//Call   IRQcallback
	GP_IRQ_CallBack[4]() ;

}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & 1<<5 )	{EXTI->PR |= 1<<5  ;   GP_IRQ_CallBack[5]() ;}
	if(EXTI->PR & 1<<6 )	{EXTI->PR |= 1<<6  ;   GP_IRQ_CallBack[6]() ;}
	if(EXTI->PR & 1<<7 )	{EXTI->PR |= 1<<7  ;   GP_IRQ_CallBack[7]() ;}
	if(EXTI->PR & 1<<8 )	{EXTI->PR |= 1<<8  ;   GP_IRQ_CallBack[8]() ;}
	if(EXTI->PR & 1<<9 )	{EXTI->PR |= 1<<9  ;   GP_IRQ_CallBack[9]() ;}

}

void EXTI10_15_IRQHandler(void)
{
	if(EXTI->PR & 1<<10 )	{EXTI->PR |= 1<<10  ;   GP_IRQ_CallBack[10]() ;}
	if(EXTI->PR & 1<<11 )	{EXTI->PR |= 1<<11  ;   GP_IRQ_CallBack[11]() ;}
	if(EXTI->PR & 1<<12 )	{EXTI->PR |= 1<<12  ;   GP_IRQ_CallBack[12]() ;}
	if(EXTI->PR & 1<<13 )	{EXTI->PR |= 1<<13  ;   GP_IRQ_CallBack[13]() ;}
	if(EXTI->PR & 1<<14 )	{EXTI->PR |= 1<<14  ;   GP_IRQ_CallBack[14]() ;}
	if(EXTI->PR & 1<<15 )	{EXTI->PR |= 1<<15  ;   GP_IRQ_CallBack[15]() ;}


}

