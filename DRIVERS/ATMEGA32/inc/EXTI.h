/*
 * EXTI.h
 *
 * Created: 3/4/2023 12:58:47 PM
 *  Author: Mohamed
 */ 


#ifndef EXTI_H_
#define EXTI_H_

#include "../ATmega.h"
#include "DIO.h"

//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef	struct
{
	uint8_t		EXTI_NUMBER;					//the number of EXTI you want to Enable it 			
												//can be choose according to @ref_EXTI_NUMBER	
												
	uint8_t		Trigger_Case ;				  //when the interrupt happen
											 //can be choose according to @ref_EXTI_TRIGGER
			
	
	void(*P_IRQ_Handler)(void);			 // set the function which will be call at IRQ happen
	
	}EXTI_PinConfig_t;




//-----------------------------
//Macros Configuration References
//-----------------------------



//@ref_EXTI_NUMBER
#define			INT0			0
#define			INT1			1
#define			INT2			2

	
//@ref_EXTI_TRIGGER
/* Hint : INT2 can be EXTI_FALLING_Edge_trigger or EXTI_RAISING_Edge_trigger ONLY */
#define	EXTI_FALLING_Edge_trigger		0
#define EXTI_RAISING_Edge_trigger		1
#define EXTI_LOW_LEVEL_CHANGE			2
#define EXTI_ANY_LOGIC_CHANGE			3


/*
* ===============================================
* APIs Supported by "MCAL EXTI DRIVER"
* ===============================================
*/

void MCAL_EXTI_INT(EXTI_PinConfig_t* EXTI_Config  );
void MCAL_EXTI_DEINIT(void);





#endif /* EXTI_H_ */