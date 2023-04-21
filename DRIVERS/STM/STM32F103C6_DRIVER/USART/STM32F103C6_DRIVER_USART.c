/*
 * USART.c
 *
 *  Created on: APr 21, 2023
 *      Author: Mohamed
 */


#include "STM32F103C6_DRIVER_USART.h"
#include "STM32F103C6_DRIVER_RCC.h"
#include "STM32F103C6_DRIVER_GPIO.h"
#include "STM32F103C6_DRIVER_EXTI.h"



//=================================================================
//********************Generic Variables****************************
//=================================================================

USART_config* Global_UART1_Config ;
USART_config* Global_UART2_Config ;
USART_config* Global_UART3_Config ;

//=================================================================
//********************Generic Functions****************************
//=================================================================


void(*UARTP_IQR_Callback)(enum UART_IRQ_Event flag);


//=================================================================
//*********************************APIS****************************
//=================================================================

/**================================================================
 * @Fn				-MCAL_USART_Init
 * @brief		    -Initialize UART (Support ASYNCH only)
 * @param [in] 		-USARTx :where x can be (1,2,3 .. depending on device used )
 * @param [in]	    -USARTx_Config: make the configuration information for specific UART PIN
 * @retval		    -none
 * Note				-support now Asynch mode & Clock 8 MHz
 *
 */


void MCAL_USART_INIT(USART_typeDef* USARTx , USART_config* USARTx_Config  )
{


	if (USARTx == USART1)
	{ Global_UART1_Config = USARTx_Config ;}
	else if (USARTx == USART2)
	{ Global_UART2_Config = USARTx_Config ;}
	else
	{ Global_UART3_Config = USARTx_Config ;}

	uint32_t PCLK , BRR ;

	//CLock enable for UASRT
	if(USARTx == USART1)
	{ RCC_USART1_CLK_EN() ;}
	else if(USARTx == USART2)
	{ RCC_USART2_CLK_EN() ;}
	else if(USARTx == USART3)
	{ RCC_USART3_CLK_EN() ;}

	//USART enable Module
	USARTx->CR1 |=(1<<13);

	//Enable TX/RX
	USARTx->CR1 |= USARTx_Config->Mode ;

	//PAYLOAD Width
	USARTx->CR1 |= USARTx_Config->Paybad_length ;

	//Parity Control bit field
	USARTx->CR1 |= USARTx_Config->Parity_BIT ;

	//number of stop Bits
	USARTx->CR2 |= USARTx_Config->Stop_BIT ;

	//Hardware flow control
	USARTx->CR3 |= USARTx_Config->HD_Flow_Control ;


	//configuration Baud rate
	//USART1 		  ---->PCLK2
	//USART2 & USART3 ---->PCLK1

	if(USARTx == USART1)
	{
		PCLK = MCAL_RCC_GET_PCLK2_Freq();
	}
	else
	{ PCLK =  MCAL_RCC_GET_PCLK1_Freq(); }

	BRR = UART_BRR_Register(PCLK , USARTx_Config->Baund_rate );

	USARTx->BRR = BRR ;

	// Enable and Disable interrupt
	//USART_CR1
	if(USARTx_Config->IQR_Enable != UART_IQR_Enable_NONE)
	{
		USARTx->CR1 |= (USARTx_Config->IQR_Enable) ;
		//NVIC Enable
		if(USARTx == USART1)
		{
			NVIC_IRQ37_USART1_Enable ;
		}
		else if(USARTx == USART2)
		{
			NVIC_IRQ38_USART2_Enable ;
		}
		else if (USARTx == USART3)
		{ NVIC_IRQ39_USART3_Enable ;}

	}


}

/**================================================================
 * @Fn				-MCAL_USART_DEINIT
 * @brief		    -Deinit UART peripheral
 * @param [in] 		-USARTx :where x can be (1,2,3 .. depending on device used )
 * @retval		    -none
 * Note				-none
 *
 */


void MCAL_USART_DEINIT(USART_typeDef* USARTx )
{
	if (USARTx == USART1)
	{
		RCC_USART1_CLK_RESET();
		NVIC_IRQ37_USART1_Disable ;
	}
	else if (USARTx == USART2)
	{
		RCC_USART2_CLK_RESET();
		NVIC_IRQ38_USART2_Disable;
	}
	else if (USARTx == USART3)
	{
		RCC_USART3_CLK_RESET();
		NVIC_IRQ39_USART3_Disable ;
	}

}

/**================================================================
 * @Fn				-MCAL_USART_GPIO_SET_PINS
 * @brief		    -initialize  GPIO pins
 * @param [in] 		-USARTx :where x can be (1,2,3 .. depending on device used )
 * @retval		    -none
 * Note				-should enable corresponding ALT and GPIO in RCC clock
 *
 */


void MCAL_USART_GPIO_SET_PINS(USART_typeDef* USARTx)
{
	GPIO_pinConfig_t pincfg;
	if (USARTx == USART1)
	{
		//PA9  =>TX  --> output alternative push pull
		//PA10 =>RX	 --> alternative input
		//PA11 =>CTS --> input floating
		//PA12 =>CTR --> output alternative push pull


		//PA9
		pincfg.GPIO_PIN_NUMBER = GPIO_PIN9 ;
		pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
		pincfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOA, &pincfg);

		//PA10
		pincfg.GPIO_PIN_NUMBER = GPIO_PIN10 ;
		pincfg.GPIO_MODE = GPIO_MODE_INPUT_AF_ ;
		MCAL_GPIO_Init(GPIOA, &pincfg);

		//PA11
		if(Global_UART1_Config->HD_Flow_Control == USART_TX_mode || Global_UART1_Config->HD_Flow_Control == USART_TX_RX_mode)
		{
			pincfg.GPIO_PIN_NUMBER =GPIO_PIN11 ;
			pincfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOA, &pincfg);
		}
		//PA12
		if(Global_UART1_Config->HD_Flow_Control == USART_RX_mode || Global_UART1_Config->HD_Flow_Control == USART_TX_RX_mode)
		{
			pincfg.GPIO_PIN_NUMBER = GPIO_PIN12 ;
			pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			pincfg.GPIO_OUTPUT_SPEED =GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOA, &pincfg);
		}

	}
	else if (USARTx == USART2)
	{
		//PA2  =>TX  --> output alternative push pull
		//PA3  =>RX	 --> alternative input
		//PA0  =>CTS --> input floating
		//PA1  =>CTR --> output alternative push pull


		//PA2
		pincfg.GPIO_PIN_NUMBER = GPIO_PIN2 ;
		pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
		pincfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOA, &pincfg);

		//PA3
		pincfg.GPIO_PIN_NUMBER = GPIO_PIN3 ;
		pincfg.GPIO_MODE = GPIO_MODE_INPUT_AF_ ;
		MCAL_GPIO_Init(GPIOA, &pincfg);

		//PA0
		if(Global_UART2_Config->HD_Flow_Control == USART_TX_mode || Global_UART2_Config->HD_Flow_Control == USART_TX_RX_mode)
		{
			pincfg.GPIO_PIN_NUMBER =GPIO_PIN0 ;
			pincfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOA, &pincfg);
		}
		//PA1
		if(Global_UART2_Config->HD_Flow_Control == USART_RX_mode || Global_UART2_Config->HD_Flow_Control == USART_TX_RX_mode)
		{
			pincfg.GPIO_PIN_NUMBER = GPIO_PIN1 ;
			pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			pincfg.GPIO_OUTPUT_SPEED =GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOA, &pincfg);
		}

	}
	else if (USARTx == USART3)
	{
		//PB10  =>TX  --> output alternative push pull
		//PB11 =>RX	 --> alternative input
		//PB13 =>CTS --> input floating
		//PB14 =>CTR --> output alternative push pull


		//PB10
		pincfg.GPIO_PIN_NUMBER = GPIO_PIN10 ;
		pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
		pincfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOB, &pincfg);

		//PB11
		pincfg.GPIO_PIN_NUMBER = GPIO_PIN11 ;
		pincfg.GPIO_MODE = GPIO_MODE_INPUT_AF_ ;
		MCAL_GPIO_Init(GPIOB, &pincfg);

		//PB13
		if(Global_UART3_Config->HD_Flow_Control == USART_TX_mode || Global_UART3_Config->HD_Flow_Control == USART_TX_RX_mode)
		{
			pincfg.GPIO_PIN_NUMBER =GPIO_PIN13 ;
			pincfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOB, &pincfg);
		}
		//PB14
		if(Global_UART3_Config->HD_Flow_Control == USART_RX_mode || Global_UART3_Config->HD_Flow_Control == USART_TX_RX_mode)
		{
			pincfg.GPIO_PIN_NUMBER = GPIO_PIN14 ;
			pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			pincfg.GPIO_OUTPUT_SPEED =GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOB, &pincfg);
		}

	}



}


/**================================================================
 * @Fn				-MCAL_USART_SEND_DATA
 * @brief		  	-Send data by USART
 * @param [in] 		-USARTx:	 	where x can be (1,2,3 .. depending on device used )
 * @param [in] 		-pTXBuffer:	 	Data you want to send it
 * @param [in] 		-polling_EN:	enable polling or diable it
 * @retval 			-none
 * Note				-none
 */
void MCAL_USART_SEND_DATA(USART_typeDef* USARTx , uint16_t* pTXBuffer , enum polling_mechanism polling_EN )
{

	if(USARTx == USART1)
	{
		//wait until TXE flag is set in SR
		if(polling_EN == POLLING_Enable)
		{
			while(! (USARTx->SR & 1<<7) );
		}

		//Check Word length is 9BIT or 8BIT
		if(Global_UART1_Config->Paybad_length == UART_Payload_9BIT)
		{
			USARTx->DR = (*pTXBuffer & (uint16_t)0x01FF); //9 BIT

		}
		else
		{
			USARTx->DR = (*pTXBuffer & (uint8_t)0xFF) ;//8BIT
		}

	}
	else if (USARTx == USART2)
	{
		//wait until TXE flag is set in SR
		if(polling_EN == POLLING_Enable)
		{
			while(! (USARTx->SR & 1<<7) );
		}

		//Check Word length is 9BIT or 8BIT
		if(Global_UART2_Config->Paybad_length == UART_Payload_9BIT)
		{
			USARTx->DR = (*pTXBuffer & (uint16_t)0x01FF); //9 BIT

		}
		else
		{
			USARTx->DR = (*pTXBuffer & (uint8_t)0xFF) ;//8BIT
		}

	}
	else if (USARTx == USART3)
	{
		//wait until TXE flag is set in SR
		if(polling_EN == POLLING_Enable)
		{
			while(! (USARTx->SR & 1<<7) );
		}

		//Check Word length is 9BIT or 8BIT
		if(Global_UART3_Config->Paybad_length == UART_Payload_9BIT)
		{
			USARTx->DR = (*pTXBuffer & (uint16_t)0x01FF); //9 BIT

		}
		else
		{
			USARTx->DR = (*pTXBuffer & (uint8_t)0xFF) ;//8BIT
		}

	}

}
void MCAL_USART_WAIT_TC(USART_typeDef* USARTx)
{
	//Wait until TC flag is set in SR
	//TC ------> Transmit complete
	while(! (USARTx->SR & 1<<6));
}


void MCAL_USART_RECIEVE_DATA(USART_typeDef* USARTx , uint16_t* pTXBuffer , enum polling_mechanism polling_EN)
{
	if(USARTx == USART1)
	{
		//wait until RXNE is set in SR
		if (polling_EN == POLLING_Enable)
			while(! (USARTx->SR & 1<<5));


		if(Global_UART1_Config->Paybad_length == UART_Payload_9BIT)
		{
			if(Global_UART1_Config->Parity_BIT == UART_parity_Disable)
			{
				*((uint16_t*)pTXBuffer) =USARTx->DR ;
			}
			else
			{
				//9BIT== 8 Data + 1 parity(Do not consider it)
				*((uint16_t*)pTXBuffer) =(USARTx->DR & (uint8_t)0xFF);
			}

		}
		else
		{
			if(Global_UART1_Config->Parity_BIT == UART_parity_Disable)
			{
				*((uint16_t*)pTXBuffer) =(USARTx->DR & (uint8_t)0xFF); //8 bit data send it all
			}
			else
			{
				//8BIT== 7 Data + 1 parity(Do not consider it)
				*((uint16_t*)pTXBuffer) =(USARTx->DR & (uint8_t)0x7F);
			}
		}
	}

	else if(USARTx == USART2)
	{
		//wait until RXNE is set in SR
		if (polling_EN == POLLING_Enable)
			while(! (USARTx->SR & 1<<5));


		if(Global_UART2_Config->Paybad_length == UART_Payload_9BIT)
		{
			if(Global_UART2_Config->Parity_BIT == UART_parity_Disable)
			{
				*((uint16_t*)pTXBuffer) =USARTx->DR ;
			}
			else
			{
				//9BIT== 8 Data + 1 parity(Do not consider it)
				*((uint16_t*)pTXBuffer) =(USARTx->DR & (uint8_t)0xFF);
			}

		}
		else
		{
			if(Global_UART2_Config->Parity_BIT == UART_parity_Disable)
			{
				*((uint16_t*)pTXBuffer) =(USARTx->DR & (uint8_t)0xFF); //8 bit data send it all
			}
			else
			{
				//8BIT== 7 Data + 1 parity(Do not consider it)
				*((uint16_t*)pTXBuffer) =(USARTx->DR & (uint8_t)0x7F);
			}
		}
	}
	if(USARTx == USART3)
	{
		//wait until RXNE is set in SR
		if (polling_EN == POLLING_Enable)
			while(! (USARTx->SR & 1<<5));


		if(Global_UART3_Config->Paybad_length == UART_Payload_9BIT)
		{
			if(Global_UART3_Config->Parity_BIT == UART_parity_Disable)
			{
				*((uint16_t*)pTXBuffer) =USARTx->DR ;
			}
			else
			{
				//9BIT== 8 Data + 1 parity(Do not consider it)
				*((uint16_t*)pTXBuffer) =(USARTx->DR & (uint8_t)0xFF);
			}

		}
		else
		{
			if(Global_UART3_Config->Parity_BIT == UART_parity_Disable)
			{
				*((uint16_t*)pTXBuffer) =(USARTx->DR & (uint8_t)0xFF); //8 bit data send it all
			}
			else
			{
				//8BIT== 7 Data + 1 parity(Do not consider it)
				*((uint16_t*)pTXBuffer) =(USARTx->DR & (uint8_t)0x7F);
			}
		}
	}

}

//ISR

void USART1_IRQHandler()
{
	Global_UART1_Config->UARTP_IQR_Callback() ;
}
void USART2_IRQHandler()
{
	Global_UART2_Config->UARTP_IQR_Callback() ;
}
void USART3_IRQHandler()
{
	Global_UART3_Config->UARTP_IQR_Callback() ;
}

