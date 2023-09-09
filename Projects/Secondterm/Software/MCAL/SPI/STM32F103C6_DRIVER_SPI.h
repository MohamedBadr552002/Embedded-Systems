/*
 * STM32F103C6_DRIVER_SPI.h
 *
 *  Created on: Jul 4, 2023
 *      Author: Mohamed
 */

#ifndef INC_STM32F103C6_DRIVER_SPI_H_
#define INC_STM32F103C6_DRIVER_SPI_H_

#include "stm32f103c6.h"
#include "STM32F103C6_DRIVER_GPIO.h"
#include "STM32F103C6_DRIVER_RCC.h"

//-----------------------------
//User type definitions (structures)
//-----------------------------

struct S_IRQ_SRC
{
	uint8_t TXE:1 ;  //Tx buffer empty interrupt
	uint8_t RXNE:1 ; //RX buffer not empty interrupt
	uint8_t ERRI:1 ; //Error interrupt
	uint8_t Reserved:5 ;
};

typedef struct{

	uint16_t  Device_mode ;   			//Specify the SPI operation mode @ref SPI_Device_mode
	uint16_t  Communication_Mode ;		//Specify the bidirectional mode state @ref SPI_Communication_Mode

	uint16_t  Frame_Format;				//Specify the MSB or LSB @ref SPI_Frame_Format

	uint16_t  DataSize ;				//@ref SPI_DataSize

	uint16_t  CLK_POLARITY;				//Specify the idle state of the clock @ref SPI_CLKPOLARITY

	uint16_t  CLK_PHASE;				//@ref SPI_CLK_PHASE

	uint16_t  NSS;						//Specify how NSS managed by hardware or software @ref NSS_managed

	uint16_t SPI_BAUDRATEPRESCALER;     /*Specifies the Baud Rate prescaler value which will be
										  used to configure the transmit and receive SCK clock.
										  This parameter can be a value of @ref SPI_BAUDRATEPRESCALER
										  @note The communication clock is derived from the master
										  clock. The slave clock does not need to be set.*/
										  // Take Care you have to Conigure RCC to enter the correct clock to APB2 >>> to SPI

	uint16_t  IRQ_ENABLE;				//@ref SPI_IRQ_Enable


	void(* P_IRQ_CallBack)(struct S_IRQ_SRC irq_src) ;

}SPI_Config;


//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref SPI_Device_mode
#define SPI_Device_Mode_Slave			(0x00000000U)
#define SPI_Device_Mode_Master			(0x1U<<2)

//@ref SPI_Communication_Mode
#define SPI_DIRECTION_2LINES			(0x00000000U)
#define SPI_DIRECTION_2LINES_RXONLY		(0x1U<<10)		//Receive only
#define SPI_DIRECTION_1LINES_RXONLY		(0x1U<<15)
#define SPI_DIRECTION_1LINES_TXONLY		((0x1U<<15)|(0x1U<<14))

//@ref SPI_Frame_Format
#define	SPI_MSB_TRANSMITTED_FRIST		(0x00000000U)
#define	SPI_LSB_TRANSMITTED_FRIST		(0x1U<<7)

//@ref SPI_DataSize
#define SPI_DataSize_8BIT				(0x00000000U)
#define	SPI_DataSize_16BIT				(0x1U<<11)

//SPI_CLKPOLARITY
#define SPI_CLKPOLARITY_idle_LOW		(0x00000000U)
#define SPI_CLKPOLARITY_idle_HIGH		(0x1U<<1)

//@ref SPI_CLK_PHASE
#define	SPI_CLK_PHASE_FRIST_EDGE		(0x00000000U)
#define	SPI_CLK_PHASE_SECOND_EDGE		(0x1U<<0)


//@ref NSS_managed
#define SPI_NSS_Hard_Slave                    			      ((uint16_t)0x0000)
#define SPI_NSS_Hard_Master_SS_output_enable                  (0x1U<<2)           				//SPI_CR2  Bit 2 SSOE: SS output enable
#define SPI_NSS_Hard_Master_SS_output_disable                 ~(0x1U<<2)           				//SPI_CR2  Bit 2 SSOE: SS output enable
#define SPI_NSS_Soft_NSSInternalSoft_Reset                    (0x1U<<9)							//for Master & Slave
#define SPI_NSS_Soft_NSSInternalSoft_Set                      ((0x1U<<9) | (0x1U<<8)) 			//for Master & Slave

//@ref SPI_BAUDRATEPRESCALER
#define SPI_BAUDRATEPRESCALER_2         (0x00000000U)
#define SPI_BAUDRATEPRESCALER_4         (0b001U << 3 )
#define SPI_BAUDRATEPRESCALER_8         (0b010U << 3)
#define SPI_BAUDRATEPRESCALER_16        (0b011U << 3)
#define SPI_BAUDRATEPRESCALER_32        (0b100U << 3)
#define SPI_BAUDRATEPRESCALER_64        (0b101U << 3)
#define SPI_BAUDRATEPRESCALER_128       (0b110U << 3)
#define SPI_BAUDRATEPRESCALER_256       (0b111U << 3)


//@ref SPI_IRQ_Enable
#define SPI_IRQ_Enable_NONE                      		(uint32_t)(0)
#define SPI_IRQ_Enable_TXEIE                       		(uint32_t) (1<<7) 	//SPI_CR2 Bit 7 TXEIE: Tx buffer empty interrupt enable
#define SPI_IRQ_Enable_RXNEIE                    		(uint32_t) (1<<6) //SPI_CR2 Bit 6 RXNEIE: RX buffer not empty interrupt enable
#define SPI_IRQ_Enable_ERRIE                       	    (uint32_t) (1<<5) //SPI_CR2 Bit 5 ERRIE: Error interrupt enable

enum PollingMechism{
	SPI_Pollingenable ,
	SPI_Pollingdisable
};
/*
* =======================================================================================
* 							APIs Supported by "MCAL SPI DRIVER"
* =======================================================================================
*/

void MCAL_SPI_INIT (SPI_typeDef *SPIx, SPI_Config* SPI_Config);
void MCAL_SPI_DEINIT (SPI_typeDef *SPIx);
void MCAL_SPI_GPIO_SET_PINS (SPI_typeDef *SPIx);
void MCAL_SPI_SENDDATA	(SPI_typeDef *SPIx, uint16_t *pTxBuffer,enum PollingMechism PollingEn );
void MCAL_SPI_RECIEVEDATA	(SPI_typeDef *SPIx, uint16_t *pTxBuffer ,enum PollingMechism PollingEn );
void MCAL_SPI_TX_RX	(SPI_typeDef *SPIx, uint16_t *pTxBuffer,enum PollingMechism PollingEn );
void MCAL_SPI_SLAVE_TX_RX	(SPI_typeDef *SPIx, uint16_t *pTxBuffer,uint8_t* arr,enum PollingMechism PollingEn );

//Variables for Application
//uint8_t* ptr_to_valid_pass ;


#endif /* INC_STM32F103C6_DRIVER_SPI_H_ */
