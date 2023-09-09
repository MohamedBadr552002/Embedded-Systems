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

unsigned char  Entered_ID ;


s_LCD_Config_t LCD_user={
		.s_LCDCtrlPins = {GPIOB, GPIO_PIN10, GPIO_PIN11},
		.s_LCDDataPins = {GPIOB, GPIO_PIN5},
		.e_EntryMode = NOSHIFT_DECREMENT,
		.e_DispCtrl = ONDISP_OFFCURSOR,
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


void APP_LCD_display()
{

	HAL_LCD_clearscreen(&LCD_user);
	HAL_LCD_sendstring(&LCD_user, "Welcome, Enter Your ID : ");
	LCD_delay(500);

}

void Uart_callback_fun(void)
{
	MCAL_USART_RECIEVE_DATA(USART1, &Entered_ID, POLLING_Disable);
	MCAL_USART_SEND_DATA(USART1, &Entered_ID, POLLING_Enable);

	HAL_LCD_clearscreen(&LCD_user);
	HAL_LCD_sendstring(&LCD_user, "You Enter: ");
	HAL_LCD_sendchar(&LCD_user, Entered_ID, DATA);

	//Send the ID to admin system through SPI
	MCAL_GPIO_Writepin(GPIOA, GPIO_PIN4, GPIO_PIN_RESET); //active slave select
	MCAL_SPI_TX_RX(SPI1, &Entered_ID, SPI_Pollingenable);
	MCAL_GPIO_Writepin(GPIOA, GPIO_PIN4, GPIO_PIN_SET); //active slave select

	HAL_LCD_clearscreen(&LCD_user);
	HAL_LCD_sendstring(&LCD_user ,"Checking ID >>>");
	LCD_delay(2000);
	APP_LCD_display();


}



int main(void)
{
     //============================================================
	//===================System Init ==============================
   //==============================================================

	CLOCK_INIT();

	//====================== LCD ==============================
	HAL_LCD_init(&LCD_user);

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


	//======================SPI==============================
	SPI_Config spi1;
	spi1.CLK_POLARITY = SPI_CLKPOLARITY_idle_HIGH ;
	spi1.CLK_PHASE = SPI_CLK_PHASE_SECOND_EDGE ;
	spi1.DataSize = SPI_DataSize_8BIT ;
	spi1.Frame_Format = SPI_MSB_TRANSMITTED_FRIST ;
	spi1.SPI_BAUDRATEPRESCALER = SPI_BAUDRATEPRESCALER_8 ;
	spi1.Communication_Mode =SPI_DIRECTION_2LINES ;
	spi1.Device_mode = SPI_Device_Mode_Master;
	spi1.IRQ_ENABLE =SPI_IRQ_Enable_NONE ;
	spi1.P_IRQ_CallBack =NULL;
	spi1.NSS = SPI_NSS_Soft_NSSInternalSoft_Set ;

	GPIO_pinConfig_t NSS;
	NSS.GPIO_PIN_NUMBER = GPIO_PIN4;
	NSS.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	NSS.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(GPIOA, &NSS);
	MCAL_GPIO_Writepin(GPIOA, GPIO_PIN4, GPIO_PIN_SET);

	MCAL_SPI_INIT(SPI1, &spi1);
	MCAL_SPI_GPIO_SET_PINS(SPI1);


     //============================================================
	//=================== System APP ==============================
   //==============================================================
	APP_LCD_display();





	while(1)
	{



	}

}
