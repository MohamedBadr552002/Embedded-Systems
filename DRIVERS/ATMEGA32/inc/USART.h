/*
 * USART.h
 *
 * Created: 3/6/2023 11:14:47 PM
 *  Author: Mohamed
 */ 


#ifndef USART_H_
#define USART_H_

//******************//
//INCLUDES
//******************//
#include "../ATmega.h"


//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref OPERATION MODE
#define USART_Asynchronous_Mode			0
#define USART_Synchronous_Mode			1

//@ref Parity bit
#define USART_DISABLED_PARITY			0
#define USART_EVEN_PARITY				1
#define USART_ODD_PARITY				2

//@ref Stop bit
#define USART_1BIT_STOP					0
#define USART_2BIT_STOP					1	

//@ref NUMBER OF DATA
#define USART_5BIT_SENT					0
#define USART_6BIT_SENT					1
#define USART_7BIT_SENT					2
#define USART_8BIT_SENT					3
#define USART_9BIT_SENT					4


//******************//
//API
//******************//
void MCAL_USART_INIT(uint8_t num_data, uint8_t Mode , uint8_t Parity , uint8_t stop);
void MCAL_USART_DEINIT();
void MCAL_USART_TRANSMIT(uint8_t Data);
uint8_t MCAL_USART_RECEIVE();
void MCAL_USART_SEND_STRING(uint8_t  *Data);
uint8_t MCAL_USART_RECEIVE_STRING(void);
void MCAL_USART_SEND_INTEGER(uint32_t Number);
uint32_t MCAL_USART_RECEIVE_INTEGER(void);



#endif /* USART_H_ */