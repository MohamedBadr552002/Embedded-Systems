/*
 * stm32f103c6_GPIO.h
 *
 *  Created on: Nov 2, 2022
 *      Author: Mohamed
 */

#ifndef INC_STM32F103C6_GPIO_DRIVER_H_
#define INC_STM32F103C6_GPIO_DRIVER_H_

//INCLUDES
#include "stm32f103c6.h"

//================================================================
//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct {
	uint16_t GPIO_PIN_NUMBER;  //specifies the GPIO pins to be configured.
							  //this parameter must be set based on @ref GPIO_PINS_define

	uint16_t GPIO_MODE;       //specifies the operating mode for selected pins .
	  	  	  	  	  	  	 //this parameter can value of @ref GPIO_MODE_define

	uint16_t GPIO_OUTPUT_SPEED ; //specifies the speed for selected pins .
	  	  	 	 	 	 	 	//this parameter can value of @ref GPIO_SPEED_define
}GPIO_pinConfig_t;

//-----------------------------
//Macros Configuration References
//-----------------------------

/*@ref GPIO_PINS_state */
#define GPIO_PIN_SET         1
#define GPIO_PIN_RESET		 0

/*@ref GPIO_RETURN_LOCK*/
#define GPIO_RETURN_LOCK_OK   		1
#define GPIO_RETURN_LOCK_ERROR 		0


/*@ref GPIO_PINS_define */
#define GPIO_PIN0     	((uint16_t)  0x0001)
#define GPIO_PIN1     	((uint16_t)  0x0002)
#define GPIO_PIN2     	((uint16_t)  0x0004)
#define GPIO_PIN3     	((uint16_t)  0x0008)
#define GPIO_PIN4     	((uint16_t)  0x0010)
#define GPIO_PIN5     	((uint16_t)  0x0020)
#define GPIO_PIN6     	((uint16_t)  0x0040)
#define GPIO_PIN7     	((uint16_t)  0x0080)
#define GPIO_PIN8     	((uint16_t)  0x0100)
#define GPIO_PIN9     	((uint16_t)  0x0200)
#define GPIO_PIN10    	((uint16_t)  0x0400)
#define GPIO_PIN11    	((uint16_t)  0x0800)
#define GPIO_PIN12    	((uint16_t)  0x1000)
#define GPIO_PIN13    	((uint16_t)  0x2000)
#define GPIO_PIN14    	((uint16_t)  0x4000)
#define GPIO_PIN15    	((uint16_t)  0x8000)
#define GPIO_PIN_All  	((uint16_t)  0xFFFF)

#define GPIO_PIN_MASK 	0x0000FFFU  //PIN mask for asssert test

/*@ref GPIO_MODE_define*/

//0: Analog mode
//1: Floating input (reset state)
//2: Input with pull-up
//3: Input with pull-down
//4: General purpose output push-pull
//5: General purpose output Open-drain
//6: Alternate function output Push-pull
//7: Alternate function output Open-drain
//8: Alternate function Input

#define GPIO_MODE_ANALOG          0x00000000U
#define GPIO_MODE_INPUT_FLO       0x00000001U
#define GPIO_MODE_INPUT_PU        0x00000002U
#define GPIO_MODE_INPUT_PD        0x00000003U
#define GPIO_MODE_OUTPUT_PP       0x00000004U
#define GPIO_MODE_OUTPUT_OD       0x00000005U
#define GPIO_MODE_OUTPUT_AF_PP    0x00000006U
#define GPIO_MODE_OUTPUT_AF_OD    0x00000007U
#define GPIO_MODE_INPUT_AF_       0x00000008U


/*@ref GPIO_SPEED_define*/

//1: Output mode, max speed 10 MHz.
//2: Output mode, max speed 2 MHz.
//3: Output mode, max speed 50 MHz.
#define GPIO_SPEED_10M         	  0x00000001u
#define GPIO_SPEED_2M         	  0x00000002u
#define GPIO_SPEED_50M         	  0x00000003u

/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/
void MCAL_GPIO_Init(GPIO_typeDef *GPIOx , GPIO_pinConfig_t* pinConfig);

void MCAL_GPIO_Deinit(GPIO_typeDef *GPIOx);

uint8_t MCAL_GPIO_Readpin(GPIO_typeDef *GPIOx , uint16_t pinNumber);

uint16_t MCAL_GPIO_Readport(GPIO_typeDef *GPIOx);

void MCAL_GPIO_Writepin(GPIO_typeDef *GPIOx , uint16_t pinNumber, uint8_t value);

void MCAL_GPIO_Writeport(GPIO_typeDef *GPIOx , uint16_t value);

void MCAL_GPIO_Togglepin(GPIO_typeDef *GPIOx , uint16_t pinNumber);

uint8_t MCAL_GPIO_Lockpin(GPIO_typeDef *GPIOx , uint16_t pinNumber);


#endif /* INC_STM32F103C6_GPIO_DRIVER_H_ */
