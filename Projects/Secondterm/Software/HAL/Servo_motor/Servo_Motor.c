/*
 * Servo_Motor.c
 *
 *  Created on: Aug 27, 2023
 *      Author: Mohamed
 */


#include "Servo_Motor.h"



//Direction of motion
#define UP   1
#define Down 0


//B8 SERVO1
void HAL_Servo1_Entry_Gate_Init(void)
{
	/*SERVO MOTOR 1*/
	GPIO_pinConfig_t PinCinfg;
	PinCinfg.GPIO_PIN_NUMBER=GPIO_PIN8;
	PinCinfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCinfg.GPIO_OUTPUT_SPEED =GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCinfg);
}

//Direction Up or Down
void HAL_Servo1_Entry_Gate(uint8_t Direction)
{
	if(Direction == UP)
	{
		//servo1 Enter gate up +90
		MCAL_GPIO_Writepin(GPIOB, GPIO_PIN8, 1);
		dus(500);
		MCAL_GPIO_Writepin(GPIOB, GPIO_PIN8, 0);
	}
	if(Direction==Down)
	{
		//servo1 Enter gate down -90
		MCAL_GPIO_Writepin(GPIOB, GPIO_PIN8, 1);
		dus(1488);
		MCAL_GPIO_Writepin(GPIOB, GPIO_PIN8, 0);
	}


}

//B9 SERVO2
void HAL_Servo2_Exit_Gate_Init(void)
{
	/*SERVO MOTOR 2*/
	GPIO_pinConfig_t PinCinfg;
	PinCinfg.GPIO_PIN_NUMBER=GPIO_PIN9;
	PinCinfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCinfg.GPIO_OUTPUT_SPEED =GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCinfg);
}

//Direction Up or Down
void HAL_Servo2_Exit_Gate(uint8_t Direction)
{
	if(Direction == UP)
	{
		//servo2 Exit gate up +90
		MCAL_GPIO_Writepin(GPIOB, GPIO_PIN9, 1);
		dus(500);
		MCAL_GPIO_Writepin(GPIOB, GPIO_PIN9, 0);
	}

	if(Direction == Down)
	{
		//servo2 Exit gate down -90
		MCAL_GPIO_Writepin(GPIOB, GPIO_PIN9, 1);
		dus(1488);
		MCAL_GPIO_Writepin(GPIOB, GPIO_PIN9, 0);
	}

}
