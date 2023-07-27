/*
 * Timer.c
 *
 * Created: 7/27/2023 5:08:37 PM
 *  Author: Mohamed
 */ 

#include "../INC/Timer.h"

//=================================================================
//********************Generic Variables****************************
//=================================================================
Timer_config* Global_TIMER0_Config;

//=================================================================
//*********************************APIS****************************
//=================================================================


/* ================================================================
 * @Fn 				- MCAL_TIMER0_Init
 * @brief 			- Initializes TIMER0 according to the specified parameters in Timer_Cfg
 * @param [in] 		- TIMER0_Config : a pointer to TIMER_CONFIG_t structure that contains the configuration information for the specified TIMER Module
 * @retval 			- None
 * Note 			- Supported for TIMER0 ONLY
 *
 */

void MCAL_TIMER0_INIT(Timer_config *TIMER0_Config)
{	
	SREG |= 1<<7 ;	
	TIMER0_Config = Global_TIMER0_Config;
	//set mode
	TCCR0 |= TIMER0_Config->Mode;
	// set clock source
	TCCR0 |= TIMER0_Config->ClocK_SCR;
	//enable or disable interrupt
	TCCR0 |= TIMER0_Config->IRQ_Enable ;
	
}

/* ================================================================
 * @Fn 				- MCAL_TIMER0_STOP
 * @brief 			- DeInitialze Timer0 Operation By Disable Timer Clock
 * @retval 			- None
 * Note 			- Supported for TIMER0 ONLY
 */
void MCAL_TIMER0_STOP(void)
{
	TCCR0 |= Timer_ClocK_SCR_NO_Clock;
}

/* ================================================================
 * @Fn 				- MCAL_TIMER0_GETCompareValue
 * @brief 			- Get Timer counter value
 * @param [in] 		- TicksNumber : value of counter value from counter register (TCNT0)
 * @retval 			- None
 * Note 			- None
 *
 */
void MCAL_TIMER0_GETCompareValue(uint8_t* TicksNumber)
{
	*TicksNumber = TCNT0;
}

/* ================================================================
 * @Fn 				- MCAL_TIMER0_SETCompareValue
 * @brief 			- Set OCR Register compare Value in Compare Match Mode(CTC)
 * @param [in] 		- TicksNumber : Value to Set in OCR(compare value must not exceed 255)
 * @retval 			- None
 * Note 			- Supported for Compare Match Mode(CTC) only & compare value must not exceed 255
 */
void MCAL_TIMER0_SETCompareValue(uint8_t TicksNumber)
{
	OCR0 = TicksNumber; 
}

/* ================================================================
 * @Fn 				- MCAL_PWM_DutyCycle
 * @brief 			- Set PWM duty cycle in Fast PWM Mode
 * @param [in] 		- Duty_Cycle : Value of PWM duty cycle (from 0 to 255)
 * @retval 			- None
 * Note 			- Supported for Fast PWM Mode only & count value must not exceed 255
 */
void MCAL_PWM_DUTTYCYCLE(uint8_t Duty_Cycle)
{
	if (Global_TIMER0_Config->Mode == Timer_Mode_Fast_PWM_INVERTING)
	{
		OCR0 = Duty_Cycle;
	}
	else if (Global_TIMER0_Config->Mode == Timer_Mode_Fast_PWM_NON_INVERTING)
	{
		OCR0 = (uint8_t)(255-Duty_Cycle);
	}
}

/* ================================================================ */
/* ================ ISR Functions Definations ===================== */
/* ================================================================ */

void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	Global_TIMER0_Config->P_IRQ_CallBack();
}

void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	Global_TIMER0_Config->P_IRQ_CallBack();
}
