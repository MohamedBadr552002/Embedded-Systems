/*
 * DIO.h
 *
 * Created: 2/23/2023 9:03:53 PM
 *  Author: Mohamed
 */ 


#ifndef DIO_H_
#define DIO_H_

//******************//
//INCLUDES
//******************//
#include "../ATmega.h"




typedef enum {
	PORT_A ,
	PORT_B ,
	PORT_C ,
	PORT_D
}DIO_PORT_t;



//******************//
//PINS Configration
//******************//

#define DIO_PIN_INPUT		0
#define DIO_PIN_OUTPUT		1


#define DIO_PIN_HIGH		1
#define DIO_PIN_LOW			0

//@ref PIN_NUMBER
#define DIO_PIN0		0
#define DIO_PIN1		1
#define DIO_PIN2		2
#define DIO_PIN3		3
#define DIO_PIN4		4
#define DIO_PIN5		5
#define DIO_PIN6		6
#define DIO_PIN7		7


//******************//
//API
//******************//

void MCAL_DIO_INIT_PIN(DIO_PORT_t  PORTX , uint8_t PIN_NUMBER , uint8_t MODE);
void MCAL_DIO_WRITE_PIN(DIO_PORT_t PORTX , uint8_t PIN_NUMBER ,uint8_t VALUE);
uint8_t MCAL_DIO_READ_PIN(uint8_t PORTX , uint8_t PIN_NUMBER);
void MCAL_DIO_TOGGLE_PIN(DIO_PORT_t PORTX , uint8_t PIN_NUMBER);
void MCAL_DIO_WRITE_PORT( DIO_PORT_t PORTX , uint8_t VALUE  ); 



#endif /* DIO_H_ */