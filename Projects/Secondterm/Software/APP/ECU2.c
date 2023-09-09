/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mohamed Badr
 * @brief          : Main program body
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif



#include "stm32f103c6.h"
#include "STM32F103C6_DRIVER_GPIO.h"
#include "keybad.h"
#include "LCD.h"
#include "7_segments.h"
#include "I2C_slave_EEPROM.h"
#include "Servo_Motor.h"
#include "STM32F103C6_DRIVER_EXTI.h"
#include "STM32F103C6_DRIVER_RCC.h"
#include "STM32F103C6_DRIVER_USART.h"
#include "STM32F103C6_DRIVER_SPI.h"
#include "STM32F103C6_DRIVER_I2C.h"
#include "STM32F103C6_DRIVER_TIMER.h"

#define F_CPU	10000000

#define UP   1
#define Down 0

uint8_t Gate_Command ='c';
uint8_t Num_of_slots = 3;



void CLOCK_INIT(void)
{
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN() ;
}


void _delay(int ms){
	volatile uint32_t counter =0;
	for(int i =0;i<ms;i++){
		for(;counter<1500;counter++);
	}
}


void _7Segment_Update(uint8_t num)
{
	switch(num)
	{

	case 1:
		HAL_7SEGMENT_OUT(GPIOA, ONE);
		break;
	case 2:
		HAL_7SEGMENT_OUT(GPIOA, TWO);
		break;
	case 3:
		HAL_7SEGMENT_OUT(GPIOA, THREE);
		break;
	default:
		HAL_7SEGMENT_OUT(GPIOA, ZERO);
		break;
	}
	_delay(3000);
}

void EXTI5PB5_OPEN_EXIT_GATE()
{
	HAL_Servo2_Exit_Gate(UP);
	_delay(2000);

	while(MCAL_GPIO_Readpin(GPIOB, GPIO_PIN5)==1);
	HAL_Servo2_Exit_Gate(Down);
	_delay(2000);
	_7Segment_Update(++number_of_slots);
}


void Uart_callback_fun()
{
	MCAL_USART_RECIEVE_DATA(USART1, &Gate_Command, POLLING_Disable);
	if(Gate_Command == 'o')
	{
		HAL_Servo1_Entry_Gate(UP);
		_delay(2000);

		_7Segment_Update(--number_of_slots);

	}
	while(MCAL_GPIO_Readpin(GPIOB, GPIO_PIN4)== 1); // wait until PIR detect no thing
	Gate_Command = 'c'; //set the default value
	HAL_Servo1_Entry_Gate(Down);
	_delay(2000);
}

int main(void)
{
     //============================================================
	//===================System Init ==============================
   //==============================================================

	CLOCK_INIT();
	MCAL_Timer2_init();
	//===================UART==============================
	USART_config uart1 ;

	uart1.Baund_rate = UART_BaudRate_115200 ;
	uart1.HD_Flow_Control = UART_HWFlowCtl_NONE ;
	uart1.IQR_Enable = UART_IQR_Enable_RXNETE ;
	uart1.Mode = USART_TX_RX_mode ;
	uart1.Parity_BIT =UART_parity_Disable ;
	uart1.Paybad_length = UART_Payload_8BIT ;
	uart1.Stop_BIT = UART_StOP_1BIT ;
	uart1.UARTP_IQR_Callback = Uart_callback_fun ;

	MCAL_USART_INIT(USART1 , &uart1);
	MCAL_USART_GPIO_SET_PINS(USART1);


	//=============== SERVOES ==============================
	HAL_Servo1_Entry_Gate_Init();
	HAL_Servo2_Exit_Gate_Init();

	//=============== PIRs =================================
	//PIR1 A7
	GPIO_pinConfig_t PIR1;
	PIR1.GPIO_PIN_NUMBER=GPIO_PIN4;
	PIR1.GPIO_MODE = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(GPIOB, &PIR1);

	//PIR2 A1
	EXTI_Pinconfig_t PIR2 ;
	PIR2.EXTI_PIN = EXTI5PB5;
	PIR2.Trigger_Case = EXTI_TRIGGER_RAISING ;
	PIR2.P_IRQ_CallBack = EXTI5PB5_OPEN_EXIT_GATE ;
	PIR2.IRQ_EN = EXTI_IRQ_ENABLE;
	MCAL_EXTI_INIT(&PIR2);

	//=============== 7 Segment ==============================
	HAL_7SEGMENT_INIT();

	HAL_7SEGMENT_OUT(GPIOA, THREE);

	while(1)
	{

	}


}
