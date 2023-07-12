/*
 * I2C.c
 *
 * Created: 7/9/2023 12:34:00 PM
 *  Author: Mohamed
 */ 


#include "../INC/I2C.h"

//PC0	----->SCL
//PC1	----->SDL



/*
 * ===============================================================
 *                      Generic Variable
 * ===============================================================
 */
I2C_Config *Global_I2C_cfg = NULL;

	


/**================================================================
* @Fn				-MCAL_I2C_INIT
* @brief		  	-Initializes the I2C  according to the specified parameters in the I2C_cfg
* 					 
* @param [in] 		-I2C_cfg: configuration information for  I2C
* 					 take a pointer to function (this function calling at interrupt)
* @retval 			-none
* Note				-none
*/
void MCAL_I2C_INIT(I2C_Config* I2C_cfg)
{	
	//make a copy
	Global_I2C_cfg = I2C_cfg;
	//Enable I2C 
	TWCR |=(1<<2);
	//set the address
	TWAR |=(I2C_cfg->I2C_General_Call_Address_Detection);
	TWAR |=(I2C_cfg->I2C_Own_Address <<1);
	//Set interrupt stats
	if (I2C_cfg->I2C_IQR == I2C_IQR_ENABLE)
	{
		TWCR |=(I2C_cfg->I2C_IQR);
		SREG |=1<<7;   //enable external interrupt
	}
	else
	{
		TWCR |=(I2C_cfg->I2C_IQR);
		SREG &=~(1<<7);	//Disable external interrupt
	}
	//Set speed
	TWBR =(uint8_t)(((F_CPU/I2C_cfg->I2C_speed)-16)/(2*1)) ;  
	//Enable Acknowledge
	TWCR |=(1<<6);
	
}

void MCAL_I2C_DINIT(void)
{
}
/**================================================================
* @Fn				-MCAL_I2C_MASTER_TX
* @brief		  	-send data by I2C from master to slave , data must be 8
* @param [in] 		-PTXBuffer:  the data to be send
* @param [in] 		-Address: slave address
* @retval 			-none
* Note				-this function contains the I2C_GENERATE_START and I2C_Generate_Stop function .
*/
void MCAL_I2C_MASTER_TX( uint8_t Address , uint8_t PTXBuffer )
{
	//Send start Bit
	I2C_GENERATE_START();
	
	//send address
	TWDR = Address ;
	
	//wait for ACK
	TWCR |=(1<<7);
	while(!(GET_FLAG_STATUS(TWINT)));
	
	//send date
	TWDR = PTXBuffer;
	
	//wait for ACK
	TWCR |=(1<<7);
	while(!(GET_FLAG_STATUS(TWINT)));
	
	//Send stop it
	I2C_GENERATE_STOP();
	
}

/**================================================================
* @Fn				-MCAL_I2C_MASTER_RX
* @brief		  	-Receive  data by I2C from slave tto master , data must be 8 .
* @param [in] 		-Address: slave address
* @retval 			-none
* Note				-this function contains the I2C_GENERATE_START and I2C_GENERATE_STOP function .
*/
uint8_t MCAL_I2C_MASTER_RX( uint8_t Address )
{		
		uint8_t data ;
		//Send start Bit
		I2C_GENERATE_START();
		
		//send address
		TWDR = Address ;
		
		//wait for ACK
		TWCR |=(1<<7);
		while(!(GET_FLAG_STATUS(TWINT)));
		
		// receive data from slave
		TWCR |=(1<<7) ;
		while(!(GET_FLAG_STATUS(TWINT))); // Wait until receive ACK from Slave ( complete receive data )
		if(GET_FLAG_STATUS(M_DATA_Received))
		{
			//ERROR
		}
		// return data and generate stop
		data= TWDR ;
		I2C_GENERATE_STOP();
		return data;	
}


/**================================================================
* @Fn				-MCAL_I2C_SLAVE_TX
* @brief		  	-send data by I2C from  slave to master , data must be 8
* @param [in] 		-PTXBuffer:  the data to be send
* @retval 			-none
* Note				-none.
*/
void MCAL_I2C_SLAVE_TX( uint8_t PTXBuffer ) 
{
		// wait until receive address from master
		while(!(GET_FLAG_STATUS(TWINT)));
		
		//send data 
		TWDR = PTXBuffer;
		TWCR |=(1<<7);
	
		while(!(GET_FLAG_STATUS(TWINT)));
		
		// clear flag
		TWCR |=(1 << 7) ;	

	
}

/**================================================================
* @Fn				-MCAL_I2C_SLAVE_RX
* @brief		  	-Receive data by I2C from  master to slave , data must be 8
* @retval 			-return data received from master .
* Note				-none.
*/
uint8_t MCAL_I2C_SLAVE_RX( void) 
{	
	uint8_t data ;
	// set ACK , enable I2C , clear flag
	TWCR =(1 << 7) | (1 << 6) | (1 << 2);
	// wait until receive address
	while(!(GET_FLAG_STATUS(TWINT)));
	
	// receive data from master
	TWCR =(1 << 7) | (1 << 6) | (1 << 2);
	while(!(GET_FLAG_STATUS(TWINT)));
	
	// return data
	data = TWDR ;
	return data;
	
}
	
	

void I2C_GENERATE_START( void )
{
		TWCR =(1<<7) | (1<<5) | (1<<2) ;
		while(!(GET_FLAG_STATUS(TWINT)));
		if(GET_FLAG_STATUS(START_Transmitted))
		{
			//ERROR
		}
}

void I2C_GENERATE_STOP(void )
{
	TWCR =(1<<7) | (1<<4) |(1<<2) ;
}


/**================================================================
* @Fn				-GET_FLAG_STATUS
* @brief		  	-check the current state to I2C ( busy , receive data , receive address ...... ) .
* @param [in] 		-flag: the status to be check
* @retval 			-FlagStatus
* Note				-none
*/
FlagStatus GET_FLAG_STATUS(  Status flag )
{
		FlagStatus current_state ;
		switch( flag )
		{
			case TWINT :
			if (TWCR & 1<<7 )
			current_state=SET ;
			else
			current_state=RESET ;
			break;
			case START_Transmitted :
			if ((TWSR & 0XF8) != 0X08 )
			current_state=SET ;
			else
			current_state=RESET ;
			break;
			case SLA_W_Transmitted :
			if ((TWSR & 0XF8) != 0X18 )
			current_state=SET ;
			else
			current_state=RESET ;
			break;
			case M_DATA_Transmitted :
			if ((TWSR & 0XF8) != 0X28 )
			current_state=SET ;
			else
			current_state=RESET ;
			break;
			case SLA_W_Received :
			if ((TWSR & 0XF8) != 0X60 )
			current_state=SET ;
			else
			current_state=RESET ;
			break;
			case S_DATA_Received :
			if ((TWSR & 0XF8) != 0X80 )
			current_state=SET ;
			else
			current_state=RESET ;
			break;
			case SLA_R_Transmitted :
			if ((TWSR & 0XF8) != 0X40 )
			current_state=SET ;
			else
			current_state=RESET ;
			break;
			case M_DATA_Received :
			if ((TWSR & 0XF8) != 0X50 )
			current_state=SET ;
			else
			current_state=RESET ;
			break;
			case SLA_R_Received :
			if ((TWSR & 0XF8) != 0XA8 )
			current_state=SET ;
			else
			current_state=RESET ;
			break;
			case S_DATA_Transmitted :
			if ((TWSR & 0XF8) != 0XB8 )
			current_state=SET ;
			else
			current_state=RESET ;
			break;
		}
		return current_state ;
}	

/*
 * ===============================================================
 *
 *                      ISR Function Definitions
 *
 * ===============================================================
 */


void __vector_19 (void) __attribute__((signal));
void __vector_19 (void)
{
	Global_I2C_cfg->P_IRQ_CALL() ;
}
