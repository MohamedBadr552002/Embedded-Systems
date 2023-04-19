/*
 * USART.c
 *
 * Created: 3/6/2023 11:14:22 PM
 *  Author: Mohamed
 */ 


#include "../INC/USART.h"


/**================================================================
* @Fn				-MCAL_USART_INIT
* @brief		  	-Initializes the USART according to the specified parameters 
*
* @param [in] 		-num_data: configuration for the number of data you want to sent identify according to @ref NUMBER OF DATA
* @param [in] 		-Mode	:  configure the Operation Mode identify according to @ref OPERATION MODE
* @param [in] 		-Parity:   configure the Parity BIT according to @ref Parity bit
* @param [in] 		-stop:     configure the Stop BIT according to @ref Stop bit
* @retval 			-none
* Note				-none
*/



void MCAL_USART_INIT(uint8_t num_data, uint8_t Mode , uint8_t Parity , uint8_t stop)
{	
	//baud rate
	UBRRL = 51;  //9600
	
	//Enable Receiving and transmitting
	UCSRB |=(1<<4);		// enable Receiving
	UCSRB |=(1<<3);		// enable transmitting
	
	//Operation Mode
	if (Mode == USART_Synchronous_Mode)
	{
		UCSRC |=(1<<6);
	}
	else{	UCSRC &= ~(1<<6); }
		
		
	//Parity Configuration
	if (Parity == USART_EVEN_PARITY)
	{	
		UCSRC |= ( 1<<7 ) ; //This bit selects between accessing the UCSRC or the UBRRH Register. It is read as one when reading UCSRC.
		UCSRC |=(0b10<<4);
	}
	else if (Parity == USART_ODD_PARITY)
	{	
		UCSRC |= ( 1<<7 ) ; //This bit selects between accessing the UCSRC or the UBRRH Register. It is read as one when reading UCSRC.
		UCSRC |=(0b11<<4);
	}
	else
	{
		UCSRC |=(0b00<<4);
	}
	// Stop BIT 
	if (stop == USART_2BIT_STOP)
	{
		UCSRC |=(1<<3);
	}
	else
	{
		UCSRC &=~(1<<3);
	}
	//number of data 
	if (num_data == USART_5BIT_SENT)
	{
		UCSRC &=~(0b11<<1);
		UCSRB &=~(1<<2);
	}
	else if (num_data == USART_6BIT_SENT)
	{
		UCSRC |=(0b01<<1);
		UCSRB &=~(1<<2);
	}
	else if (num_data == USART_7BIT_SENT)
	{
		UCSRC |=(0b10<<1);
		UCSRB &=~(1<<2);
	}
	else if (num_data == USART_9BIT_SENT)
	{
		UCSRC |=(0b11<<1);
		UCSRB |=(1<<2);
	}
	else
	{
		UCSRC |=(0b11<<1);
		UCSRB &=~(1<<2);	
	}
	
	
		
}

/**================================================================
* @Fn				-MCAL_USART_DEINIT
* @brief		  	-RESET the USART Prephiral
*
* @retval 			-none
* Note				-none
*/

void MCAL_USART_DEINIT()
{
	UBRRL = 0 ;
	UCSRB = 0 ;
	UCSRC = 0b10000110;
	//UBRRH = 0;
	UCSRA &=~(1<<1)	;
}

/**================================================================
* @Fn				-MCAL_USART_TRANSMIT
* @brief		  	-Send data by USART
*
* @param [in] 		-Data:	 Data you want to send it
* @retval 			-none
* Note				-none
*/
void MCAL_USART_TRANSMIT(uint8_t Data)
{
	while( !((UCSRA>>5) & 1));  // check if read to send
	UDR = Data ;
}

/**================================================================
* @Fn				-MCAL_USART_RECEIVE
* @brief		  	-Receive data by USART
*
* @param [in] 		-none 
* @retval 			-the received data 
* Note				-none
*/
uint8_t MCAL_USART_RECEIVE()
{
	while (!((UCSRA >> 7) & 1));   // check if read to receive
	return UDR ;
	
}

/**================================================================
* @Fn				-MCAL_USART_SEND_STRING
* @brief		  	-Send String by USART
*
* @param [in] 		-Data:	the String you want to send it
* @retval 			-none
* Note				-none
*/

void MCAL_USART_SEND_STRING(uint8_t  *Data)
{
	uint8_t *p = Data;
	
	while(*p != '#')
	{
		while( !((UCSRA>>5) & 1));
		MCAL_USART_TRANSMIT(*p);
		p++;
	}
}

/**================================================================
* @Fn				-MCAL_USART_RECEIVE_STRING
* @brief		  	-Receive String by USART
*
* @param [in] 		-none
* @retval 			-the received String
* Note				-none
*/
uint8_t MCAL_USART_RECEIVE_STRING(void)
{
	uint8_t *p = (uint8_t) (UDR);
	while(*p != "#")
	{
		while(!((UCSRA>>7) & 1));
		p++;
		return UDR;
	}
}
/**================================================================
* @Fn				-MCAL_USART_SEND_INTEGER
* @brief		  	-Send An intgeer number by USART
*
* @param [in] 		-Number:	the number you want to send it
* @retval 			-none
* Note				-none
*/

void MCAL_USART_SEND_INTEGER(uint32_t Number)
{
	uint8_t *p = &Number;
	while( !((UCSRA>>5) & 1));
	MCAL_USART_TRANSMIT(p[0]);
	MCAL_USART_TRANSMIT(p[1]);
	MCAL_USART_TRANSMIT(p[2]);
	MCAL_USART_TRANSMIT(p[3]);
}

/**================================================================
* @Fn				-MCAL_USART_RECEIVE_INTEGER
* @brief		  	-Receive number by USART
*
* @param [in] 		-none
* @retval 			-the received number
* Note				-none
*/
uint32_t MCAL_USART_RECEIVE_INTEGER(void)
{
	uint32_t Number ;
	uint8_t *p = (uint8_t)&Number;
	while(!((UCSRA>>7) & 1));
	p[0] = MCAL_USART_RECEIVE();
	p[1] = MCAL_USART_RECEIVE();
	p[2] = MCAL_USART_RECEIVE();
	p[3] = MCAL_USART_RECEIVE();
	return Number ;
}
