/*
 * ATmega.h
 *
 * Created: 2/23/2023 9:07:16 PM
 *  Author: Mohamed
 */ 


#ifndef ATMEGA_H_
#define ATMEGA_H_

#include "stdlib.h"
#include "stdint.h"


//#define  (unsigned char)	(uint8_t)

//******************//
//Registers Addreses
//******************//

#define SFIOR  *((volatile uint32_t *)0x50)			//Special FunctionIO Register


//DIO
// PORTA
#define PORTA	*(volatile uint8_t *)(0x3B)
#define DDRA	*(volatile uint8_t *)(0x3A)
#define PINA	*(volatile uint8_t *)(0x39)

// PORTB
#define PORTB	*(volatile uint8_t *)(0x38)
#define DDRB	*(volatile uint8_t *)(0x37)
#define PINB	*(volatile uint8_t *)(0x36)

// PORTC
#define PORTC	*(volatile uint8_t *)(0x35)
#define DDRC	*(volatile uint8_t *)(0x34)
#define PINC	*(volatile uint8_t *)(0x33)

// PORTD
#define PORTD	*(volatile uint8_t *)(0x32)
#define DDRD	*(volatile uint8_t *)(0x31)
#define PIND	*(volatile uint8_t *)(0x30)







#endif /* ATMEGA_H_ */