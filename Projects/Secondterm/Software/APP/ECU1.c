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


uint8_t valid_password[3]={0};
unsigned char  ch , Motors_command ='c';


s_LCD_Config_t LCD_admin={
		.s_LCDCtrlPins = {GPIOB, GPIO_PIN10, GPIO_PIN11},
		.s_LCDDataPins = {GPIOB, GPIO_PIN12},
		.e_EntryMode = NOSHIFT_DECREMENT,
		.e_DispCtrl = ONDISP_BLINKCURSOR,
		.e_OperMode = FOURBIT_2LINE_10DOT,

};

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


void RESET_LEDS()
{
	_delay(4000);

	MCAL_GPIO_Writepin(GPIOA, GPIO_PIN0, GPIO_PIN_SET);
	MCAL_GPIO_Writepin(GPIOA, GPIO_PIN1, GPIO_PIN_SET);

}

uint8_t Admin_System_Check_ID(uint8_t ID)
{


	for(int i=0;i<3;i++)
	{
		if(ID == valid_password[i])
		{
			 MCAL_GPIO_Writepin(GPIOA, GPIO_PIN0, GPIO_PIN_RESET);

			return 'o';
		}
	}
	MCAL_GPIO_Writepin(GPIOA, GPIO_PIN1, GPIO_PIN_RESET);

	return'c';

}



void ADMIN_ENTER_PASSOWERD(void)
{
	for(int i=0;i<3;i++)
	{
		do
		{
			valid_password[i]=HAL_KEYPAD_GETCHAR();
		}
		while(valid_password[i]=='A');
		HAL_LCD_sendstring(&LCD_admin, "You enter : ");
		HAL_LCD_sendchar(&LCD_admin, valid_password[i], DATA);
		LCD_delay(300);
		HAL_LCD_clearscreen(&LCD_admin);
	}
}

void spi_callback(struct S_IRQ_SRC irq)
{

	if(irq.RXNE)
	{
		ch=0xf;
		MCAL_SPI_TX_RX(SPI1, &ch, POLLING_Disable);
		Motors_command = Admin_System_Check_ID(ch);  //Check validation of IDs
		MCAL_USART_SEND_DATA(USART1, &Motors_command, POLLING_Enable);
		RESET_LEDS();

	}

}

int main(void)
{
     //============================================================
	//=================== System Init =============================
   //==============================================================

	CLOCK_INIT();

	//=================== keypad ==============================
	HAL_KEYPAD_INIT();


	//=================== LCD ==============================
	HAL_LCD_init(&LCD_admin);


	//===================UART==============================
	USART_config uart1 ;

	uart1.Baund_rate = UART_BaudRate_115200 ;
	uart1.HD_Flow_Control = UART_HWFlowCtl_NONE ;
	uart1.IQR_Enable = UART_IQR_Enable_NONE ;
	uart1.Mode = USART_TX_RX_mode ;
	uart1.Parity_BIT =UART_parity_Disable ;
	uart1.Paybad_length = UART_Payload_8BIT ;
	uart1.Stop_BIT = UART_StOP_1BIT ;
	uart1.UARTP_IQR_Callback = NULL ;

	MCAL_USART_INIT(USART1 , &uart1);
	MCAL_USART_GPIO_SET_PINS(USART1);

	//=======================SPI==============================
	SPI_Config spi1;

	spi1.CLK_POLARITY = SPI_CLKPOLARITY_idle_HIGH ;
	spi1.CLK_PHASE = SPI_CLK_PHASE_SECOND_EDGE ;
	spi1.DataSize = SPI_DataSize_8BIT ;
	spi1.Frame_Format = SPI_MSB_TRANSMITTED_FRIST ;
	spi1.SPI_BAUDRATEPRESCALER = SPI_BAUDRATEPRESCALER_8 ;
	spi1.Communication_Mode =SPI_DIRECTION_2LINES ;
	spi1.Device_mode =SPI_Device_Mode_Slave;
	spi1.IRQ_ENABLE =SPI_IRQ_Enable_RXNEIE ;
	spi1.P_IRQ_CallBack = spi_callback ;
	spi1.NSS = SPI_NSS_Hard_Slave ;

	MCAL_SPI_INIT(SPI1, &spi1);
	MCAL_SPI_GPIO_SET_PINS(SPI1);


	//======================= LEDs ==============================
	GPIO_pinConfig_t G_LED ;

	G_LED.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	G_LED.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	G_LED.GPIO_PIN_NUMBER = GPIO_PIN0;

	MCAL_GPIO_Init(GPIOA, &G_LED);
	MCAL_GPIO_Writepin(GPIOA, GPIO_PIN0, GPIO_PIN_SET);

	GPIO_pinConfig_t R_LED ;

	R_LED.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	R_LED.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	R_LED.GPIO_PIN_NUMBER = GPIO_PIN1;

	MCAL_GPIO_Init(GPIOA, &R_LED);
	MCAL_GPIO_Writepin(GPIOA, GPIO_PIN1, GPIO_PIN_SET);

	//============================================================
   //=================== System APP ==============================
  //==============================================================


	HAL_LCD_sendstring(&LCD_admin, "WORKING....");
	LCD_delay(100);
	HAL_LCD_clearscreen(&LCD_admin);
	LCD_delay(100);
	HAL_LCD_sendstring(&LCD_admin, "Enter passwords =>");

	ADMIN_ENTER_PASSOWERD();


	for(int i=0;i<3;i++)
	{
		HAL_LCD_sendstring(&LCD_admin, "passward is : ");
		HAL_LCD_sendchar(&LCD_admin, valid_password[i], DATA);
		LCD_delay(300);
		HAL_LCD_clearscreen(&LCD_admin);
	}



	while (1)
	{

	}

}
