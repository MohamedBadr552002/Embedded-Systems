/*
 * ADC.c
 *
 * Created: 7/30/2023 5:35:10 PM
 *  Author: Mohamed
 */ 

#include "../INC/ADC.h"

void MCAL_ADC_INIT(ADC_config* cfg)
{
	//identify Vref
	ADMUX |= cfg->V_ref ;
	
	//identify pre-scaler
	ADCSRA &= 0xF8 ;
	ADCSRA |= cfg->pre_scaler ;
	
	//Enable ADC
	ADCSRA |= (1<<7);
}
uint16_t MCAL_ADC_READ_CHANNEL(ADC_CHANELS ch)
{
	//identify by MUX the operated channel 
	ADMUX &= 0xE0;
	ADMUX |= ch;
	
	// start convertion
	ADCSRA |=(1<<6);
	
	while(((ADCSRA&(1<<6))>>6));
	
	
	return ADC ;
	
}
