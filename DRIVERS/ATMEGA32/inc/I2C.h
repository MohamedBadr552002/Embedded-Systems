/*
 * I2C.h
 *
 * Created: 7/9/2023 12:33:37 PM
 *  Author: Mohamed
 */ 


#ifndef I2C_H_
#define I2C_H_


#include "../ATmega.h"


typedef struct{
	
	uint8_t		 I2C_Device_mode;			//@ref I2C_Device_mode  <NOTE:THIS PARAMETER WILL NOT BE USED IN IMPLEMENTATION JUST FOR CLEARIFICATION >
	
	uint8_t		I2C_Own_Address;			
	
	uint8_t		I2C_PreScaler;				//@ref I2C_PRESCALER
	
	uint8_t		I2C_speed;					//@ref	I2C_SPEED
	
	uint8_t		I2C_General_Call_Address_Detection ; //@ref I2C_General_Call_Address_Detection 
	
	uint8_t		I2C_IQR;				//@ref	I2C_IQR
	
	void (*P_IRQ_CALL)();				// set the function which will be call at IRQ happen
		
}I2C_Config;







// * =======================================================================================
//                               Reference Macros
// * =======================================================================================

//@ref I2C_DEVICE_MODE
#define I2C_DEVICE_MODE_MASTER		1
#define I2C_DEVICE_MODE_SLAVE		0

//@ref I2C_PRESCALER
#define	I2C_PRESCALER_1				(0b00<<0)
#define	I2C_PRESCALER_4				(0b01<<0)
#define	I2C_PRESCALER_16			(0b10<<0)
#define	I2C_PRESCALER_64			(0b11<<0)

//@ref I2C_GENERAL_CALL_ADDRESS_DETECTION
#define I2C_GENERAL_CALL_ADDRESS_DETECTION_ENABLE			(1<<0)
#define I2C_GENERAL_CALL_ADDRESS_DETECTION_DISABLE			(0<<0)

//@ref	I2C_IQR
#define I2C_IQR_ENABLE			(1<<0)
#define I2C_IQR_DISBLE			(0<<0)

//@ref	I2C_SPEED
#define I2C_SPEED_50		(50000U)
#define I2C_SPEED_100		(100000U)
#define I2C_SPEED_150		(150000U)
#define I2C_SPEED_200		(200000U)



typedef enum
{
	TWINT,
	START_Transmitted	,
	SLA_W_Transmitted   ,
	SLA_R_Transmitted   ,
	M_DATA_Transmitted	,
	SLA_W_Received		,
	SLA_R_Received		,
	S_DATA_Received		,
	S_DATA_Transmitted	,
	M_DATA_Received		,
}Status;


typedef enum
{
	RESET,
	SET
}FlagStatus;

/*
* ===============================================
* APIs Supported by "MCAL I2C DRIVER"
* ===============================================
*/

void MCAL_I2C_INIT(I2C_Config* I2C_Config);
void MCAL_I2C_DINIT(void);
void MCAL_I2C_MASTER_TX( uint8_t Address , uint8_t PTXBuffer );
uint8_t MCAL_I2C_MASTER_RX( uint8_t Address );
void MCAL_I2C_SLAVE_TX( uint8_t PTXBuffer  ) ;
uint8_t MCAL_I2C_SLAVE_RX( void) ;
//---------------------------------------------------------
//				Generic  APIS
//---------------------------------------------------------
FlagStatus GET_FLAG_STATUS(  Status flag );

void I2C_GENERATE_START( void );

void I2C_GENERATE_STOP(void );

#endif /* I2C_H_ */
