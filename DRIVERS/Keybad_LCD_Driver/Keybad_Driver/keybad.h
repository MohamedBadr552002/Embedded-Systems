/*
 * keybad.h
 *
 * Created: 12/2/2022 1:39:24 AM
 *  Author: Mohamed
 */ 


#ifndef KEYBAD_H_
#define KEYBAD_H_
#define F_CPU   1000000UL

#include <avr/io.h>
#include <util/delay.h>

#define KEYBAD_PORT				PORTD
#define DataDir_KEYBAD_CTRL		DDRD
#define KEYBAD_PIN				PIND

#define R0		0
#define R1		1
#define R2		2
#define R3		3
		
#define C0		4
#define C1		5
#define C2		6
#define C3		7

void KEYBAD_INIT(void);
void KEYBAD_GETCHAR();


#endif /* KEYBAD_H_ */