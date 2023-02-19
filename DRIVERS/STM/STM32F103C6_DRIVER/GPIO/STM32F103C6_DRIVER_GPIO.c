/*
 * STM32F103C6_DRIVER_GPIO.c
 *
 *  Created on: Feb 16, 2023
 *      Author: Mohamed
 */

#include "STM32F103C6_DRIVER_GPIO.h"

uint8_t GET_position_CRLH(uint16_t pinNumber)
{
	switch(pinNumber){
	case GPIO_PIN0:
		return 0;
		break;
	case GPIO_PIN1:
		return 4;
		break;
	case GPIO_PIN2:
		return 8;
		break;
	case GPIO_PIN3:
		return 12;
		break;
	case GPIO_PIN4:
		return 16;
		break;
	case GPIO_PIN5:
		return 20;
		break;
	case GPIO_PIN6:
		return 24;
		break;
	case GPIO_PIN7:
		return 28;
		break;
	case GPIO_PIN8:
		return 0;
		break;
	case GPIO_PIN9:
		return 4;
		break;
	case GPIO_PIN10:
		return 8;
		break;
	case GPIO_PIN11:
		return 12;
		break;
	case GPIO_PIN12:
		return 16;
		break;
	case GPIO_PIN13:
		return 20;
		break;
	case GPIO_PIN14:
		return 24;
		break;
	case GPIO_PIN15:
		return 28;
		break;
	}
	return 0;
}

/**================================================================
* @Fn				-MCAL_GPIO_Init
* @brief		    -Initialize GPIOx PINy according to specific parameters in  the pinConfig
* @param [in] 		-GPIOx :where x can be (A..E depending on device used ) to select the GPIO peripherals
* @param [in]	    -pinConfig make the configuration information for specific GPIO PIN
* @retval		    -none
* Note				-STM32F103C6 MCU has GPIO [A B C D] Modules
* 					 but LQFP48 has only GPIO A,B and part of C and D exported as external pins
*
*/

void MCAL_GPIO_Init(GPIO_typeDef *GPIOx , GPIO_pinConfig_t* pinConfig)
{

	//port configuration register LOW configure pins from 0 >> 7
	//port configuration register HIGH configure pins from 8 >> 15

	volatile uint32_t* configregister =NULL ;
	uint8_t PIN_config =0 ;

	configregister = (pinConfig ->GPIO_PIN_NUMBER < GPIO_PIN8)? &GPIOx->CRL : &GPIOx->CRH ;

	//clear CNF8[1:0] MODE[1:0]
	(*configregister) &= ~(0xF << GET_position_CRLH(pinConfig->GPIO_PIN_NUMBER ));

	//if PIN is output
	if( (pinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_OD) || (pinConfig->GPIO_MODE ==GPIO_MODE_OUTPUT_AF_PP) || (pinConfig->GPIO_MODE ==GPIO_MODE_OUTPUT_OD)||(pinConfig->GPIO_MODE ==GPIO_MODE_OUTPUT_PP))
	{
		//SET CNF8[1:0] MODE[1:0]
		PIN_config = ( (((pinConfig->GPIO_MODE - 4)<<2) | (pinConfig->GPIO_OUTPUT_SPEED)) & 0x0F ) ;


	}
	// if pin is input
	else
	{
		if((pinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO) || (pinConfig->GPIO_MODE == GPIO_MODE_ANALOG))
		{
			//SET CNF8[1:0] MODE[1:0]
			PIN_config = ( ((( pinConfig->GPIO_MODE) << 2 ) | 0x0) & 0x0F);
		}
		else if(pinConfig->GPIO_MODE == GPIO_MODE_INPUT_AF_) //consider it as input floating
		{
			//SET CNF8[1:0] MODE[1:0]
			PIN_config = ( (( GPIO_MODE_INPUT_FLO << 2 ) | 0x0) & 0x0F) ;

		}
		else //PILUP or PULLDOWN
		{
			PIN_config = ( (((GPIO_MODE_INPUT_PU) <<2) | 0x0) & 0x0F);
			if(pinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU)
			{
				GPIOx->ODR |= pinConfig->GPIO_PIN_NUMBER ;
			}
			else
			{
				GPIOx->ODR &= ~(pinConfig->GPIO_PIN_NUMBER);
			}
		}
	}
	//write on CRL or CRH
	(*configregister) |= (PIN_config << GET_position_CRLH(pinConfig ->GPIO_PIN_NUMBER) );
}

/**================================================================
* @Fn				-MCAL_GPIO_Deinit
* @brief		    -RESET all GPIOx PINS
* @param [in] 		-GPIOx :where x can be (A..E depending on device used ) to select the GPIO peripherals
* @retval		    -none
* Note				-none
*
*/

void MCAL_GPIO_Deinit(GPIO_typeDef *GPIOx)
{
	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |=(1<<2);  //Bit 2 IOPARST: IO Port A reset
		RCC->APB2RSTR &= ~(1<<2);
	}
	else if (GPIOx == GPIOB)
	{
		RCC->APB2RSTR |=(1<<3);  //Bit 3 IOPARST: IO Port A reset
		RCC->APB2RSTR &= ~(1<<3) ;
	}
	else if (GPIOx == GPIOC)
	{
			RCC->APB2RSTR |=(1<<4);  //Bit 4 IOPARST: IO Port A reset
			RCC->APB2RSTR &= ~(1<<4) ;
	}
	else if (GPIOx == GPIOD)
	{
			RCC->APB2RSTR |=(1<<5);  //Bit 3 IOPARST: IO Port A reset
			RCC->APB2RSTR &= ~(1<<5) ;
	}
	else if (GPIOx == GPIOE)
	{
			RCC->APB2RSTR |=(1<<6);  //Bit 3 IOPARST: IO Port A reset
			RCC->APB2RSTR &= ~(1<<6) ;

	}


/*if you Do not have RESET controller in your Micro controller */
/*
	GPIOx->BRR   = 0x00000000 ;
	GPIOx->BSRR  = 0x00000000 ;
	GPIOx->CRH   = 0x44444444 ;
	GPIOx->CRL   = 0x44444444 ;
//	GPIOx->IDR = ;(Read only)
	GPIOx->LCKR  = 0x00000000 ;
	GPIOx->ODR	 = 0x00000000 ;
*/
}

/**================================================================
* @Fn				-MCAL_GPIO_Readpin
* @brief		    -Read specific GPIOx PINy
* @param [in] 		-GPIOx :where x can be (A..E depending on device used ) to select the GPIO peripherals
* @param [in]	    -pinNumber : pin number you want to read it according to @ref GPIO_PINS_define
* @retval		    -the input pin val (according to @ref GPIO_PINS_state)
* Note				-none
*
*/


uint8_t MCAL_GPIO_Readpin(GPIO_typeDef *GPIOx , uint16_t pinNumber)
{

	if( ( (GPIOx->IDR) & pinNumber) != (uint32_t)GPIO_PIN_RESET)
	{
		return GPIO_PIN_SET;
	}
	else
	{
		return GPIO_PIN_RESET;
	}



}

/**================================================================
* @Fn				-MCAL_GPIO_Readport
* @brief		    -Read specific GPIOx PORT
* @param [in] 		-GPIOx :where x can be (A..E depending on device used ) to select the GPIO peripherals
* @param [in]	    -pinNumber : pin number you want to read it according to @ref GPIO_PINS_define
* @retval		    -the input pin val (according to @ref GPIO_PINS_state)
* Note				-none
*
*/

uint16_t MCAL_GPIO_Readport(GPIO_typeDef *GPIOx)
{
	uint16_t portValue ;

	portValue = (uint16_t)GPIOx->IDR ;
	return portValue;
}

/**================================================================
* @Fn				-MCAL_GPIO_Writepin
* @brief		    -Write on specific GPIOx PINy
* @param [in] 		-GPIOx :where x can be (A..E depending on device used ) to select the GPIO peripherals
* @param [in]	    -pinNumber : pin number you want to read it according to @ref GPIO_PINS_define
* @param [in]       -value : value you want to set the pin by it
* @retval		    -value of port
* Note				-none
*
*/


void MCAL_GPIO_Writepin(GPIO_typeDef *GPIOx , uint16_t pinNumber, uint8_t value)
{
	if( value != GPIO_PIN_RESET)
	{
		/*
		    Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
			These bits are write-only and can be accessed in Word mode only.
			0: No action on the corresponding ODRx bit
			1: Reset the corresponding ODRx bit
			Note: If both BSx and BRx are set, BSx has priority
		*/
		GPIOx->BSRR = (uint32_t)pinNumber;
	}
	else
	{
		/*
		 Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
		These bits are write-only and can be accessed in Word mode only.
		0: No action on the corresponding ODRx bit
		1: Reset the corresponding ODRx bit
		 */
		GPIOx->BRR = (uint32_t)pinNumber;

	}
}

/**================================================================
* @Fn				-MCAL_GPIO_Writeport
* @brief		    -Write on specific GPIOx PORT
* @param [in] 		-GPIOx :where x can be (A..E depending on device used ) to select the GPIO peripherals
* @param [in]       -value : value you want to set the port by it
* @retval		    -none
* Note				-none
*
*/


void MCAL_GPIO_Writeport(GPIO_typeDef *GPIOx , uint16_t value)
{
	GPIOx->ODR = (uint32_t)value ;
}

/**================================================================
* @Fn				-MCAL_GPIO_Togglepin
* @brief		    -toggle a specific GPIOx PORT
* @param [in] 		-GPIOx :where x can be (A..E depending on device used ) to select the GPIO peripherals
* @param [in]       -pinNumber : pin number you want to toggle it according to @ref GPIO_PINS_define
* @retval		    -none
* Note				-none
*
*/

void MCAL_GPIO_Togglepin(GPIO_typeDef *GPIOx , uint16_t pinNumber)
{

		GPIOx->ODR ^= pinNumber ;

}

/**================================================================
* @Fn				-MCAL_GPIO_Lockpin
* @brief		    -the Locking mechanism allow the IO Configuration to be FROZEN
* @param [in] 		-GPIOx :where x can be (A..E depending on device used ) to select the GPIO peripherals
* @param [in]       -pinNumber : pin number you want to lock it according to @ref GPIO_PINS_define
* @retval		    -OK is pin config is locked or ERROR if pin is not locked (accord @ref GPIO_RETURN_LOCK)
* Note				-none
*
*/


uint8_t MCAL_GPIO_Lockpin(GPIO_typeDef *GPIOx , uint16_t pinNumber)
{

/*


Bit 16 LCKK[16]: Lock key
This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
0: Port configuration lock key not active
1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
LOCK key writing sequence:
Write 1
Write 0
Write 1
Read 0
Read 1 (this read is optional but confirms that the lock is active)
Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
Any error in the lock sequence will abort the lock.
Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
These bits are read write but can only be written when the LCKK bit is 0.
0: Port configuration not locked
1: Port configuration locked
*/

	//SET lCKy[16]
	volatile uint32_t temp = 1<<16;

	temp |= pinNumber ;

	//Write 1
	GPIOx->LCKR =temp;
	//Write 0
	GPIOx->LCKR = pinNumber;
	//Write 1
	GPIOx->LCKR =temp;
	//Read 0
	temp = GPIOx->LCKR ;
	//Read 1

	if((uint32_t)GPIOx->LCKR & 1<<16 )
	{
		return GPIO_RETURN_LOCK_OK ;
	}
	else
	{
		return GPIO_RETURN_LOCK_ERROR ;

	}



}
