/*
 * SPI.c
 *
 * Created: 7/5/2023 4:28:24 PM
 *  Author: Mohamed
 */ 


#include "../INC/SPI.h"


/**================================================================
 * @Fn			-MCAL_SPI_INIT.
 * @brief	    -initialize the SPI according to config instance spi.
 * @param [in] 	-spi: pointer to SPI_config that contains SPI configuration.
 * @retval 		-none
 * Note			-none
 */
void MCAL_SPI_INIT(SPI_Config *spi)
{
	if(spi->SPI_mode) //master
	{
		//SS PIN 4 PORTB
		MCAL_DIO_INIT_PIN(PORT_B,DIO_PIN4,DIO_PIN_OUTPUT);
		MCAL_DIO_WRITE_PIN(PORT_B,DIO_PIN4 , DIO_PIN_HIGH);
		
		//MOSI	PIN5 PORTB
		MCAL_DIO_INIT_PIN(PORT_B ,DIO_PIN5 , DIO_PIN_OUTPUT);
		
		//MISO	PIN6 PORTB
		//When the SPI is enabled as a Master,this pin is configured as an input
		MCAL_DIO_INIT_PIN(PORT_B , DIO_PIN6 , DIO_PIN_INPUT);
		
		//SCLK PIN7 PORT
		MCAL_DIO_INIT_PIN(PORT_B , DIO_PIN7 , DIO_PIN_OUTPUT);
		
	}
	else
	{
		//SS PIN 4 PORTB
		MCAL_DIO_INIT_PIN(PORT_B,DIO_PIN4,DIO_PIN_INPUT);
				
		//MOSI	PIN5 PORTB
		MCAL_DIO_INIT_PIN(PORT_B ,DIO_PIN5 , DIO_PIN_INPUT);
		
		//MISO	PIN6 PORTB
		MCAL_DIO_INIT_PIN(PORT_B , DIO_PIN6 , DIO_PIN_OUTPUT);
		
		//SCLK PIN7 PORT
		MCAL_DIO_INIT_PIN(PORT_B , DIO_PIN7 , DIO_PIN_INPUT);
			
	}	
	
	//SPI enable
	SPCR |=(1<<6);
	//Data Order
	SPCR |=((spi->Data_Order)<<5);
	//Master/Slave Select
	SPCR |=((spi->SPI_mode)<<4);
	//Clock Polarity
	SPCR |=((spi->Clock_Polarity)<<3);
	//Clock Phase
	SPCR |=((spi->Clock_Phase <<2));
	//Clock Rate
	SPCR |=((spi->Clock_Rate)<<0);
		
	
	
}
/**================================================================
 * @Fn			-MCAL_SPI_DEINIT.
 * @brief	    -deinitialize the SPI.
 * @param [in] 	-none
 * @retval 		-none
 * Note			-none
 */
void MCAL_SPI_DEINIT()
{
	while(!((SPSR>>7) & 1));
	SPCR &= ~(1<<6);
	
}
/**================================================================
 * @Fn			-MCAL_SPI_TX_RX.
 * @brief	    -transmits and receives the data through SPI.
 * @param [in] 	-Data: data to be transmitted.
 * @retval 		-Received data
 * Note			-none
 */
uint8_t MCAL_SPI_TX_RX(uint8_t Data)
{
	if(((SPCR>>4) & 1))
	{
		MCAL_DIO_WRITE_PIN(PORT_B ,DIO_PIN4 , DIO_PIN_LOW);
	}
	SPDR = Data ;
	while(!((SPSR>>7) & 1));
	
	Data =SPDR ;
	
		if(((SPCR>>4) & 1))
		{
			MCAL_DIO_WRITE_PIN(PORT_B ,DIO_PIN4 , DIO_PIN_HIGH);
		}
		
		return Data ;
	
}
