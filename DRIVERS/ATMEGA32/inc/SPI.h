/*
 * SPI.h
 *
 * Created: 7/5/2023 4:27:46 PM
 *  Author: Mohamed
 */ 


#ifndef SPI_H_
#define SPI_H_

//******************//
//INCLUDES
//******************//
#include "../ATmega.h"
#include "DIO.h"

typedef struct {
	uint8_t		SPI_mode ;		//Specify device mode@ref SPI_MODE
	
	uint8_t		Data_Order;		//specify which will send frist LSB or MSB	@ref DATA_OREDER
	
	uint8_t		Clock_Polarity;	//specify the clock status in idle	@ref CLOCK_POLARITY
	
	uint8_t		Clock_Phase;	//determine if data is sampled on the leading (first) or trailing (last) edge of SCK	@ref CLOCK_PHASE
	
	uint8_t		Clock_Rate;		//control the SCK rate of the device configured as a Master	@ref CLOCK_RATE
		
	}SPI_Config;


//--------------------------------------------------------------------------------------------------------------------
//Macros Configuration References
//--------------------------------------------------------------------------------------------------------------------

//@ref SPI_MODE
#define SPI_SLAVE_MODE		0
#define SPI_MASTER_MODE		1


//@ref DATA_OREDER
#define SPI_MSB_FRIST_SENT		0
#define SPI_LSB_FRIST_SENT		1

//@ref CLOCK_POLARITY
#define	SPI_LOW_IDLE			0
#define	SPI_HIGH_IDLE			1

//@ref CLOCK_PHASE
#define SPI_CLOCK_PHASE_FRIST		0
#define SPI_CLOCK_PHASE_SECOND		1


//@ref CLOCK_RATE
#define SPI_CLOCK_RATE_4			(0b00)				
#define SPI_CLOCK_RATE_16			(0b01)
#define SPI_CLOCK_RATE_64			(0b01)
#define SPI_CLOCK_RATE_128			(0b11)


// ====================================================================================================================
//													APIs 
// ====================================================================================================================

void MCAL_SPI_INIT(SPI_Config *spi);
void MCAL_SPI_DEINIT();
uint8_t MCAL_SPI_TX_RX(uint8_t Data);	

#endif /* SPI_H_ */
