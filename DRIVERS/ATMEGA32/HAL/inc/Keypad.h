/*
 * Keypad.h
 *
 * Created: 2/25/2023 7:30:22 PM
 *  Author: Mohamed
 */ 

#define F_CPU 8000000UL
#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../ATmega.h"



#define KEYPAD_PORT				PORTD
#define DataDir_KEYPAD_CTRL		DDRD
#define KEYPAD_PIN				PIND

#define R0		0
#define R1		1
#define R2		2
#define R3		3

#define C0		4
#define C1		5
#define C2		6
#define C3		7

void KEYPAD_INIT(void);
char KEYPAD_GETCHAR();





#endif /* KEYPAD_H_ */