/*
 * ADC.h
 *
 * Created: 7/30/2023 5:35:21 PM
 *  Author: Mohamed
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "../ATmega.h"


//-----------------------------
//User type definitions (structures)
//-----------------------------
typedef struct  
{
	uint8_t		V_ref;				// indicates the conversion range for the ADC.	@ref ACD_VRef
	
	uint8_t		pre_scaler;			//determine the division factor between the XTAL frequency and the input clock to the ADC.	
									// @ref ADC_Prescaler							
}ADC_config;


typedef enum {
		CH0=0,
		CH1,
		CH2,
		CH3,
		Ch4,
		CH5,
		CH6,
		CH7,
		
	}ADC_CHANELS;



//-----------------------------------
//Macros Configuration References
//-----------------------------------

//@ref ACD_VRef
#define ACD_VRef_AREF	(0b00<<6)			// Internal Vref turned of
#define ACD_VRef_AVCC	(0b01<<6)		   //with external capacitor at AREF pin
#define ACD_VRef_256V	(0b11<<6)		  //Internal 2.56V Voltage Reference


// @ref ADC_Prescaler	
#define ADC_Prescaler_2			(0b000<<0)	
#define ADC_Prescaler_4			(0b010<<0)	
#define ADC_Prescaler_8			(0b011<<0)	
#define ADC_Prescaler_16		(0b100<<0)
#define ADC_Prescaler_32		(0b101<<0)	
#define ADC_Prescaler_64		(0b110<<0)
#define ADC_Prescaler_128		(0b111<<0)	

/* ================================================================ */
/* ========================= APIs  ================================ */
/* ================================================================ */	


void MCAL_ADC_INIT(ADC_config* cfg);
uint16_t MCAL_ADC_READ_CHANNEL(ADC_CHANELS ch);

	
#endif /* ADC_H_ */
