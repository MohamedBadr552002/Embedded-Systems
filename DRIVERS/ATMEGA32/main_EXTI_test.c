/*
 * ATmega32.c
 *
 * Created: 2/23/2023 9:02:20 PM
 * Author : Mohamed
 */ 



#include "INC/DIO.h"
#include "INC/EXTI.h"
#include "util/delay.h"
#include "HAL/inc/LCD.h"


#define F_CPU 1000000UL




void _IintteruptSR(void)
{
	
	LCD_INIT();
	LCD_WRITE_STRING("Interrupt happen");
	MCAL_DIO_TOGGLE_PIN(PORT_D , DIO_PIN7);
	_delay_ms(5000);
	
	
}

void EXTI_init()
{
	EXTI_PinConfig_t  eint_1 ;	
	eint_1.EXTI_NUMBER = INT0 ;
	eint_1.Trigger_Case = EXTI_ANY_LOGIC_CHANGE ;
	eint_1.P_IRQ_Handler =  _IintteruptSR ;
	MCAL_EXTI_INT(&eint_1);
}



int main(void)
{	
	
	
	
	 
		MCAL_DIO_INIT_PIN(PORT_D , DIO_PIN5 ,DIO_PIN_OUTPUT);
		MCAL_DIO_INIT_PIN(PORT_D , DIO_PIN6 ,DIO_PIN_OUTPUT);
		MCAL_DIO_INIT_PIN(PORT_D , DIO_PIN7 ,DIO_PIN_OUTPUT);
	
	EXTI_init();
    /* Replace with your application code */
    while (1) 
    {
		
		MCAL_DIO_TOGGLE_PIN(PORT_D ,DIO_PIN5 );
		MCAL_DIO_TOGGLE_PIN(PORT_D ,DIO_PIN6 );
		_delay_ms(1000);
		
    }
}
