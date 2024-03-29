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


#define F_CPU 8000000UL

//#define  (unsigned char)	(uint8_t)

//******************//
//Registers Addreses
//******************//

#define SFIOR  *((volatile uint32_t *)0x50)			//Special FunctionIO Register
#define SREG	*(volatile uint8_t *)(0x5F)			//Status Register


////////DIO
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


/////EXTI
#define MCUCR	*(volatile uint8_t *)(0x55)			//MCU Control Register
#define MCUCSR	*(volatile uint8_t *)(0x54)			//MCU Control and Status Register	
#define GICR	*(volatile uint8_t *)(0x5B)			//General Interrupt Control Register
#define GIFR	*(volatile uint8_t *)(0x5A)			//General Interrupt Flag Register


////USART
#define UDR		*(volatile uint8_t *)(0x2C)				//USART I/O Data Register
#define UCSRA	*(volatile uint8_t *)(0x2B)				//USART Control and Status Register A
#define UCSRB	*(volatile uint8_t *)(0x2A)				//USART Control and Status Register B
#define UCSRC	*(volatile uint8_t *)(0x40)				//USART Control and Status Register C
//#define UBRRH	*(volatile uint8_t *)()					//USART Baud Rate Registers UBRRH
#define UBRRL	*(volatile uint8_t *)(0x29)				//USART Baud Rate Registers UBRRL 


////SPI
#define SPCR	*(volatile uint8_t *)(0x2D)			    //SPI Control Register
#define SPSR	*(volatile uint8_t *)(0x2E)				//SPI Status Register 
#define SPDR	*(volatile uint8_t *)(0x2F)		     	//SPI Data Register 

////I2C
#define TWDR	*(volatile uint8_t *)(0x23)				//Two-wire Serial Interface Data Register
#define TWSR	*(volatile uint8_t *)(0x21)			
#define TWBR	*(volatile uint8_t *)(0x20)
#define TWCR	*(volatile uint8_t *)(0x56)
#define TWAR	*(volatile uint8_t *)(0x22)

////TIMER
#define OCR0	*(volatile uint8_t *)(0x5C)
#define TCNT0	*(volatile uint8_t *)(0x52)
#define TCCR0	*(volatile uint8_t *)(0x53)

////ADC
#define ADC			*(volatile uint16_t *)(0x24)			//The ADC Data Register �ADCL and ADCH
#define ADCSRA		*(volatile uint8_t  *)(0x26)			//ADC Control and StatusRegister A
#define ADMUX		*(volatile uint8_t *)(0x27)			//ADC Multiplexer Selection Register
#define SFIOR		*(volatile uint8_t *)(0x50)			//Special FunctionIO Register

#endif /* ATMEGA_H_ */
