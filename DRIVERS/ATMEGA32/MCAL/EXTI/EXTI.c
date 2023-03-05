/*
 * EXTI.c
 *
 * Created: 3/4/2023 12:58:25 PM
 *  Author: Mohamed
 */ 


/*
 * ===============================================================
 *                      Generic Variable
 * ===============================================================
 */

void (*GP_IRQ_CALL[3])(void);




/**================================================================
* @Fn				-MCAL_EXTI_INT
* @brief		  	-Initializes the EXTI [0-3] according to the specified parameters in the EXTI_Config
* 					 
* @param [in] 		-EXTI_Config: configuration information for the specified EXTI from 0 to 2
* 					 take a pointer to function (this function calling at interrupt)
* @retval 			-none
* Note				-none
*/

#include "../INC/EXTI.h"



void MCAL_EXTI_INT(EXTI_PinConfig_t* EXTI_Config  )
{	
	
	SREG |= 1<<7 ;		//The Global Interrupt Enable bit must be set for the interrupts to be enabled.
	
	
	
	if(EXTI_Config->EXTI_NUMBER == INT0)
	{
		
			// Clear
			MCUCR &=~(0X3) ;
			
			if (EXTI_Config->Trigger_Case	== EXTI_FALLING_Edge_trigger)
			{
				MCUCR |= 0X2 ;
			}
			else if (EXTI_Config->Trigger_Case	== EXTI_RAISING_Edge_trigger)
			{
				MCUCR |= 0X3 ;
			}
			else if (EXTI_Config->Trigger_Case	== EXTI_LOW_LEVEL_CHANGE)
			{
				MCUCR |=(0b00 << 0);
			}
			else if (EXTI_Config->Trigger_Case == EXTI_ANY_LOGIC_CHANGE)
			{
				MCUCR |=(0b01 << 0);
			}
			
			GP_IRQ_CALL[EXTI_Config->EXTI_NUMBER] = EXTI_Config->P_IRQ_Handler ;
			
			GICR |=(1<<6);			//When the INT0 bit is set (one) and the I-bit in the Status Register (SREG) is set (one),
				            		//the external pin interrupt is enabled.
									
			//Init DIO PIN as INPUT
			MCAL_DIO_INIT_PIN(PORT_D , DIO_PIN2 , DIO_PIN_INPUT );						
	}									
	else if(EXTI_Config->EXTI_NUMBER == INT1)
	{
			// Clear
			MCUCR &=~(0X3 << 2 ) ;
			if (EXTI_Config->Trigger_Case	== EXTI_FALLING_Edge_trigger)
			{
				MCUCR |=(0b10 << 2);
			}
			else if (EXTI_Config->Trigger_Case	== EXTI_RAISING_Edge_trigger)
			{
				MCUCR |=(0b11 << 2);
			}
			else if (EXTI_Config->Trigger_Case	== EXTI_LOW_LEVEL_CHANGE)
			{
				MCUCR |=(0b00 << 2);
			}
			else if (EXTI_Config->Trigger_Case == EXTI_ANY_LOGIC_CHANGE)
			{
				MCUCR |=(0b01 << 2);
			}
			
			GP_IRQ_CALL[EXTI_Config->EXTI_NUMBER] = EXTI_Config->P_IRQ_Handler ;
			GICR |=(1<<7);			//When the INT1 bit is set (one) and the I-bit in the Status Register (SREG) is set (one),
									//the external pin interrupt is enabled.
			//Init DIO PIN as INPUT
			MCAL_DIO_INIT_PIN(PORT_D , DIO_PIN3 , DIO_PIN_INPUT );
									
	}
	else if(EXTI_Config->EXTI_NUMBER == INT2)
	{		
			// Clear
			MCUCSR &=~( 1 << 6 ) ;
		
			if (EXTI_Config->Trigger_Case	== EXTI_FALLING_Edge_trigger)
			{
				MCUCSR |=(0 << 6);
			}
			else if (EXTI_Config->Trigger_Case	== EXTI_RAISING_Edge_trigger)
			{
				MCUCSR |=(1 << 6);
			}	
			GP_IRQ_CALL[EXTI_Config->EXTI_NUMBER] = EXTI_Config->P_IRQ_Handler ;
			GICR |=(1<<5);			//When the INT2 bit is set (one) and the I-bit in the Status Register (SREG) is set (one),
									//the external pin interrupt is enabled.
			//Init DIO PIN as INPUT
			MCAL_DIO_INIT_PIN(PORT_B , DIO_PIN2 , DIO_PIN_INPUT );						
															
	}
	
}


/**================================================================
* @Fn				-MCAL_EXTI_DEINIT
* @brief		  	-Reset all the EXTI Register
* @retval 			-none
* Note				-none
*/
void MCAL_EXTI_DEINIT(void)
{
	SREG &= ~(1<<7);		//Disable Interrupts
	
	GICR &= ~(1<<5);		//Disable IN2
	GICR &= ~(1<<6);		//Disable IN0
	GICR &= ~(1<<7);		//Disable IN1
	
	MCUCSR &=~( 1 << 6 )	;
	MCUCR &=~( 0XF )		;
	
	
}

/*
 * ===============================================================
 *                      ISR Function Definitions
 * ===============================================================
 */


void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	//Call function
	GP_IRQ_CALL[0]();
	
	GIFR |=(1<<6);	
}


void __vector_2 (void) __attribute__((signal));
void __vector_2 (void)
{
	//Call function
	GP_IRQ_CALL[1]();
	
	GIFR |=(1<<7);
}


void __vector_3 (void) __attribute__((signal));
void __vector_3 (void)
{
	//Call function
	GP_IRQ_CALL[2]();
	
	GIFR |=(1<<8);
}