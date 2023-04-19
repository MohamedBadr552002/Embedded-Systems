/*
 * STM32F103C6_DRIVER_USART.h
 *
 *  Created on: Mar 16, 2023
 *      Author: Mohamed
 */

#ifndef INC_STM32F103C6_DRIVER_USART_H_
#define INC_STM32F103C6_DRIVER_USART_H_

#include "stm32f103c6.h"
#include "STM32F103C6_DRIVER_RCC.h"
#include "STM32F103C6_DRIVER_GPIO.h"




//-----------------------------
//User type definitions (structures)
//-----------------------------
typedef struct
{
	uint8_t   Mode ;      		//to Enable the transmission or Receiving  Mode or both
					     	   //this parameter must be set based on @ref USART_Mode_define

	uint32_t  Baund_rate;     //configures the communication Baund rate
							 //this parameter must be set based on @ref USART_Baund_rate_define

	uint8_t   Paybad_length; //specifies the number of data bit transmitted or received in frame
							//this parameter must be set based on @ref USART_Paybad_length_define

	uint8_t	  Stop_BIT; 	 //specifies the number of Stop bit in frame
	                        //this parameter must be set based on @ref USART_Stop_BIT_define

	uint8_t   Parity_BIT;	 //specifies the number of Stop bit in frame
							//this parameter must be set based on @ref USART_Parity_BIT_define

	uint8_t	  HD_Flow_Control;   //specifies if the HDflowControl is enable or not
								//this parameter must be set based on @ref USART_HD_Flow_Control_define

	uint8_t   IQR_Enable; 		//Specifies if the IQR is Enable or not
							   //this parameter must be set based on @ref USART_IQR_Enable_define

	void(*UARTP_IQR_Callback)(void); //	set the C function to be called

}USART_config ;


enum UART_IRQ_Event
{
	UART_IQR_TXE,
	UART_IRQ_TC,
	UART_IQR_TC,
	UART_IQR_RXINE,
	UART_IQR_ORE,
	UART_IRQ_PE
};



//-----------------------------
//Macros Configuration References
//-----------------------------


//@ref USART_Mode_define
#define USART_TX_mode			(uint32_t)(1<<3)
#define USART_RX_mode		    (uint32_t)(1<<2)
#define	USART_TX_RX_mode		(uint32_t)((1<<3)|(1<<2))

//@ref USART_Baund_rate_define
#define UART_BaudRate_2400					2400
#define	UART_BaudRate_9600					9600
#define	UART_BaudRate_19200					19200
#define UART_BaudRate_57600					57600
#define UART_BaudRate_115200				115200
#define UART_BaudRate_230400				230400
#define UART_BaudRate_460800				460800
#define UART_BaudRate_921600				921600
#define UART_BaudRate_2250000				2250000
#define UART_BaudRate_4500000				4500000

//@ref USART_Paybad_length_define
#define UART_Payload_8BIT			(uint32_t)(0<<12)
#define UART_Payload_9BIT			(uint32_t)(1<<12)

//@ref USART_Stop_BIT_define
//00: 1 Stop bit
//01: 0.5 Stop bit
//10: 2 Stop bits
//11: 1.5 Stop bit
#define UART_StOP_1BIT			(uint32_t)(0b00<<21)
#define UART_Stop_HALF_BIT		(uint32_t)(0b01<<21)
#define UART_Stop_2BIT			(uint32_t)(0b10<<21)
#define UART_Stop_1_HALF_BIT	(uint32_t)(0b11<<21)


//@ref USART_Parity_BIT_define
#define UART_parity_Disable		(uint32_t)(0<<10)
#define UART_Parity_EVEN		(uint32_t)(1<<10 | 0<<9)
#define UART_Parity_ODD		    (uint32_t)(1<<10 | 1<<9)


//@ref USART_HD_Flow_Control_define
#define UART_HWFlowCtl_NONE			(uint32_t)(0)
#define UART_HWFlowCtl_RTS			(uint32_t)(1<<8)
#define UART_HWFlowCtl_CTS			(uint32_t)(1<<9)
#define UART_HWFlowCtl_RTS_CTS		(uint32_t)(1<<8 | 1<<9)

//@ref USART_IQR_Enable_define
#define UART_IQR_Enable_NONE		(uint32_t)(0)
#define UART_IQR_Enable_TXE			(uint32_t)(1<<7)//Transmit data register empty
#define UART_IQR_Enable_TC			(uint32_t)(1<<6)//transmission complete
#define UART_IQR_Enable_RXNETE		(uint32_t)(1<<5)//Received data ready to be read and overrun error detection
#define UART_IQR_Enable_PE			(uint32_t)(1<<8)//Parity error


enum polling_mechanism
{
	POLLING_Enable ,
	POLLING_Disable
};

/****************MACROS FOR BAUD RATE *********/

//Baud rate calculation
// USARTDIV = fclk / (16 * Baud rate)
//USARTDIV_MUL100 = uint32((100 *fclk ) / (16 * Baudrate) == (25 *fclk ) / (4* Baudrate) )
//DIV_Mantissa_MUL100 = Integer Part (USARTDIV ) * 100
//DIV_Mantissa = Integer Part (USARTDIV )
//DIV_Fraction = (( USARTDIV_MUL100 - DIV_Mantissa_MUL100 ) * 16 ) / 100

#define USARTDIV(_PCLK_ , _BAUD_)				(uint32_t)(_PCLK_/(16 * _BAUD_))
#define USARTDIV_MUL100(_PCLK_ , _BAUD_)		(uint32_t)( (25 * _PCLK_) /(4 * _BAUD_))
#define Mantissa_MUL100(_PCLK_ , _BAUD_)		(uint32_t)(USARTDIV(_PCLK_ , _BAUD_)* 180)
#define Mantissa(_PCLK_ , _BAUD_)				(uint32_t)(USARTDIV(_PCLK_ , _BAUD_))
#define DIV_Fraction(_PCLK_ , _BAUD_)			(uint32_t)(((USARTDIV_MUL100(_PCLK_ ,_BAUD_) - Mantissa_MUL100(_PCLK_ ,_BAUD_)) * 16))
#define UART_BRR_Register(_PCLK_ , _BAUD_)		((Mantissa(_PCLK_ , _BAUD_)<<4) | (DIV_Fraction(_PCLK_ , _BAUD_))& 0xF )



/*
* ===============================================
* APIs Supported by "MCAL USART DRIVER"
* ===============================================
*/

void MCAL_USART_INIT(USART_typeDef* USARTx , USART_config* USARTx_Config  );
void MCAL_USART_DEINIT(USART_typeDef* USARTx );
void MCAL_USART_GPIO_SET_PINS(USART_typeDef* USARTx);
void MCAL_USART_SEND_DATA(USART_typeDef* USARTx , uint16_t* pTXBuffer , enum polling_mechanism polling_EN );
void MCAL_USART_WAIT_TC(USART_typeDef* USARTx);
void MCAL_USART_RECIEVE_DATA(USART_typeDef* USARTx , uint16_t* pTXBuffer , enum polling_mechanism polling_EN);







#endif /* INC_STM32F103C6_DRIVER_USART_H_ */
