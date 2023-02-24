/*
 * ATmega32.c
 *
 * Created: 2/23/2023 9:02:20 PM
 * Author : Mohamed
 */ 

#define F_CPU 8000000UL


#include "ATmega.h"
#include "INC/DIO.h"
#include "util/delay.h"





void DIO_INIT(void)
{
		MCAL_DIO_INIT_PIN(PORT_D , DIO_PIN5 , DIO_PIN_OUTPUT);
		MCAL_DIO_INIT_PIN(PORT_D , DIO_PIN6 , DIO_PIN_OUTPUT);
		MCAL_DIO_INIT_PIN(PORT_D , DIO_PIN7 , DIO_PIN_OUTPUT);
		MCAL_DIO_INIT_PIN(PORT_D , DIO_PIN0 , DIO_PIN_INPUT);
		

}


int main(void)
{	

	DIO_INIT();
    /* Replace with your application code */
    while (1) 
    {
		
		if (MCAL_DIO_READ_PIN(PORT_D , DIO_PIN0) == DIO_PIN_HIGH)
		{
			MCAL_DIO_TOGGLE_PIN(PORT_D , DIO_PIN5 );
			MCAL_DIO_TOGGLE_PIN(PORT_D , DIO_PIN6 );
			MCAL_DIO_TOGGLE_PIN(PORT_D , DIO_PIN7 );
			_delay_ms(1000);
		}
			
		
		
    }
}


