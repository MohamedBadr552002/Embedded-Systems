/*
 * DIO.c
 *
 * Created: 2/23/2023 9:03:29 PM
 *  Author: Mohamed
 */ 

#include "../INC/DIO.h"


/*******************************************************************************
 * Fn                -MCAL_DIO_INIT_PIN
 * Brief             -Set the PORTx PINy Nether INPUT or Output.
 *
 * Param [in]        -PORTX: where x can be (A..D depending on device used) to
 *                    select the GPIO Peripheral.
 *
 * Param [in]        -PIN_NUMBER: set pin number according @ref PIN_NUMBER .
 *
 *
 * Param [in]        -MODE: Mode which wanted to be the pin mode .
 *
 *
 * Retval            -None.
 *
 */


void MCAL_DIO_INIT_PIN(DIO_PORT_t  PORTX , uint8_t PIN_NUMBER , uint8_t MODE)
{
	
	
		if(PORTX == PORT_A )
		{
			if (MODE == DIO_PIN_INPUT)
			{	
				DDRA  &= ~(1<< PIN_NUMBER);
				
			}
			else if (MODE == DIO_PIN_OUTPUT)
			{
				DDRA  |= (1<< PIN_NUMBER);
				
			}
			else{} //error handling

		}
		else if(PORTX == PORT_B )
		{
			if (MODE == DIO_PIN_INPUT)
			{
				DDRB  &= ~(1<< PIN_NUMBER);
				
			}
			else if (MODE == DIO_PIN_OUTPUT)
			{
				DDRB  |= (1<< PIN_NUMBER);
				
			}
			else{} //error handling
		}
					
		else if(PORTX == PORT_C )
		{
			if (MODE == DIO_PIN_INPUT)
			{
				DDRC  &= ~(1<< PIN_NUMBER);
				
			}
			else if (MODE == DIO_PIN_OUTPUT)
			{
				DDRC  |= (1<< PIN_NUMBER);
				
			}
			else{} //error handling
		}
							
		else if(PORTX == PORT_D )
		{
			if (MODE == DIO_PIN_INPUT)
			{
				DDRD  &= ~(1<< PIN_NUMBER);
				
			}
			else if (MODE == DIO_PIN_OUTPUT)
			{
				DDRD  |= (1<< PIN_NUMBER);
				
			}
			else{} //error handling
		}
	
}

/*******************************************************************************
 * Fn                -MCAL_DIO_WRITE_PIN
 *
 * Brief             -Write on specific PIN.
 *
 * Param [in]        -PORTX: where x can be (A..D depending on device used) to
 *                    select the GPIO Peripheral.
 *
 * Param [in]        -PIN_NUMBER: set pin number according @ref PIN_NUMBER
 *
 *
 * Param [in]        -VALUE: value which wanted set .
 *
 * Retval            -None.
 *
 * Note              -None.
 */

void MCAL_DIO_WRITE_PIN(DIO_PORT_t PORTX , uint8_t PIN_NUMBER , uint8_t VALUE)
{
	if (PORTX == PORT_A)
	{
		if (VALUE == DIO_PIN_HIGH)
		{
			PORTA |= (1<<PIN_NUMBER) ;	
		}
		else if (VALUE == DIO_PIN_LOW)
		{
			PORTA &= ~(1<<PIN_NUMBER);
		}
		else{} //error handling
			
	}
	else if (PORTX == PORT_B)
	{
		if (VALUE == DIO_PIN_HIGH)
		{
			PORTB |= (1<<PIN_NUMBER) ;
		}
		else if (VALUE == DIO_PIN_LOW)
		{
			PORTB &= ~(1<<PIN_NUMBER);
		}
		else{} //error handling
	}
	else if(PORTX == PORT_C)
	{
		if (VALUE == DIO_PIN_HIGH)
		{
			PORTC |= (1<<PIN_NUMBER) ;
		}
		else if (VALUE == DIO_PIN_LOW)
		{
			PORTC &= ~(1<<PIN_NUMBER);
		}
		else{} //error handling
	}
	else if(PORTX == PORT_D)
	{
		if (VALUE == DIO_PIN_HIGH)
		{
			PORTD |= (1<<PIN_NUMBER) ;
		}
		else if (VALUE == DIO_PIN_LOW)
		{
			PORTD &= ~(1<<PIN_NUMBER);
		}
		else{} //error handling
	}
}

/*******************************************************************************
 * Fn                -MCAL_DIO_READ_PIN
 *
 * Brief             -Read specific PIN.
 *
 * Param [in]        -PORTX: where x can be (A..D depending on device used) to
 *                    select the PORT Peripheral.
 *
 * Param [in]        -PIN_NUMBER: set pin number  .
 *
 * Retval            -The input pin value.
 *
 * Note              -None.
 */

uint8_t MCAL_DIO_READ_PIN(DIO_PORT_t PORTX , uint8_t PIN_NUMBER)
{
	
		uint8_t value =0 ;	
		if (PORTX == PORT_A)
		{
			value =(uint8_t)(PINA &(1<<PIN_NUMBER))>>PIN_NUMBER;
			return value ;
		}
		else if (PORTX == PORT_B)
		{
			value =(uint8_t)(PINB &(1<<PIN_NUMBER))>>PIN_NUMBER;
			return value ;
		}
		else if(PORTX == PORT_C)
		{
			value =(uint8_t)(PINC &(1<<PIN_NUMBER))>>PIN_NUMBER;
			return value ;
		}
		else if(PORTX == PORT_D)
		{
			value =(uint8_t)(PIND &(1<<PIN_NUMBER))>>PIN_NUMBER;
			return value ;
		}
		else{} //error handling
	
}

/*******************************************************************************
 * Fn                -MCAL_DIO_TOGGLE_PIN
 *
 * Brief             -Toggle a specific pin in PORTx.
 *
 * Param [in]        -PORTX: where x can be (A..D depending on device used) to
 *                    select the PORT Peripheral.
 *
 * Param [in]        -PIN_NUMBER: specifies the port pin to toggle it, set pin
 *                    number according @ref PIN_NUMBER.
 *
 * Retval            -None.
 *
 * Note              -None.
 */

void MCAL_DIO_TOGGLE_PIN(DIO_PORT_t PORTX , uint8_t PIN_NUMBER)
{
	if (PORTX == PORT_A)
	{
		PORTA ^= (1<<PIN_NUMBER);
	}
	else if (PORTX == PORT_B)
	{
		PORTB ^=(1<<PIN_NUMBER);
	}
	else if(PORTX == PORT_C)
	{
		PORTC ^= (1<<PIN_NUMBER);
	}
	else if(PORTX == PORT_D)
	{
		PORTD ^= (1<<PIN_NUMBER);
	}
}


/*******************************************************************************
 * Fn                -MCAL_DIO_WRITE_PORT.
 *
 * Brief             -Write on specific PORT.
 *
 * Param [in]        -PORTX: where x can be (A..D depending on device used) to
 *                    select the GPIO Peripheral.
 *
 * Param [in]        -VALUE: Port value.
 *
 * Retval            -None.
 *
 * Note              -None.
 */
void MCAL_DIO_WRITE_PORT( DIO_PORT_t PORTX , uint8_t VALUE  )
{
	if(PORTX == PORT_A)
	{
		PORTA = VALUE ;
	}
	else if (PORTX == PORT_B)
	{
		PORTB = VALUE ;
	}
	else if (PORTX == PORT_C)
	{
		PORTC = VALUE ;
	}
	else if (PORTX == PORT_D)
	{
		PORTD = VALUE ;
	}
}
