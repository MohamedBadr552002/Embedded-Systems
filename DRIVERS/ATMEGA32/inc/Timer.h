/*
 * Timer.h
 *
 * Created: 7/27/2023 5:08:52 PM
 *  Author: Mohamed
 */ 


#ifndef TIMER_H_
#define TIMER_H_


//******************//
//INCLUDES
//******************//

#include "../ATmega.h"

//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct {
	
	uint8_t		Mode;				// Specifiy the Operation mode of timer @ref Timer_Mode
	
	uint8_t		ClocK_SCR;		   // Specifiy the timer Clock source and prescaler @Timer_ClocK_SCR
	
	uint8_t		IRQ_Enable;		  // Enable or disable the interrupts  @ref Timer_IRQ_Enable
	
	void (*P_IRQ_CallBack)(void);
	
}Timer_config;


//-----------------------------------
//Macros Configuration References
//-----------------------------------

//@ref Timer_Mode

// WGM0	WGM00
// 0	0		Normal 0xFF Immediate MAX
// 0	1		PWM, Phase Correct 0xFF TOP BOTTOM
// 1	0		CTC OCR0 Immediate MAX
// 1	1		Fast PWM 0xFF BOTTOM MAX
#define Timer_Mode_Normal						((0<<6)||(0<<3))
#define Timer_Mode_PWM							((1<<6)||(0<<3))
#define Timer_Mode_CTC							((0<<6)||(1<<3))
#define Timer_Mode_Fast_PWM_INVERTING			((1<<6)||(1<<3)||(1<<4))
#define Timer_Mode_Fast_PWM_NON_INVERTING		((1<<6)||(1<<3)||(0<<4))

//@Timer_ClocK_SCR

//CS02 CS01 CS00 Description
//0 0 0			 No clock source (Timer/Counter stopped).
//0 0 1			 clkI/O/(No prescaling)
//0 1 0		   	clkI/O/8 (From prescaler)
//0 1 1			clkI/O/64 (From prescaler)
//1 0 0			clkI/O/256 (From prescaler)
//1 0 1			clkI/O/1024 (From prescaler)
//1 1 0			External clock source on T0 pin. Clock on falling edge.
//1 1 1			External clock source on T0 pin. Clock on rising edge.

#define Timer_ClocK_SCR_NO_Clock			(0b000<<0)
#define Timer_ClocK_SCR_NO_Prescale			(0b001<<0)
#define Timer_ClocK_SCR_Clk_8				(0b010<<0)
#define Timer_ClocK_SCR_Clk_64				(0b011<<0)
#define Timer_ClocK_SCR_Clk_256				(0b100<<0)
#define Timer_ClocK_SCR_Clk_1024			(0b101<<0)
#define Timer_ClocK_SCR_EXT_Clk_Falling		(0b110<<0)
#define Timer_ClocK_SCR_EXT_Clk_Raising		(0b111<<0)


//@ref Timer_IRQ_Enable
#define TIMER0_IRQ_DISABLE										((0<<0)||(0<<1))
#define TIMER0_IRQ_ENABLE_OVER_FLOW								(1<<0)			//Timer/Counter0 Overflow Interrupt Enable
#define TIMER0_IRQ_ENABLE_COMPARE_MATCH							(1<<1)			//Timer/Counter0 Output Compare Match Interrupt Enable

/* ================================================================ */
/* =========== APIs Supported by "MCAL TIMER0 DRIVER" ============= */
/* ================================================================ */

void MCAL_TIMER0_INIT(Timer_config *TIMER0_Config);
void MCAL_TIMER0_STOP(void);

void MCAL_TIMER0_GETCompareValue(uint8_t* TicksNumber);
void MCAL_TIMER0_SETCompareValue(uint8_t TicksNumber);

void MCAL_PWM_DUTTYCYCLE(uint8_t Duty_Cycle);



#endif /* TIMER_H_ */
