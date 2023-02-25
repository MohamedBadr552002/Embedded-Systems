/*
 * Keypad.c
 *
 * Created: 2/25/2023 7:29:51 PM
 *  Author: Mohamed
 */ 

#include "inc/Keypad.h"
#include "util/delay.h"

int KEYPAD_ROWS[] ={R0 ,R1 ,R2 ,R3};
int KEYPAD_COLS[] ={C0 ,C1 ,C2 ,C3};

void KEYBAD_INIT()
{
	DataDir_KEYPAD_CTRL &= ~((1<<R0) | (1<<R1) | (1<<R2) | (1<<R3));
	DataDir_KEYPAD_CTRL |=  ((1<<C0) | (1<<C1) | (1<<C2) | (1<<C3));
	KEYPAD_PORT = 0xFF;
}

char KEYBAD_GETCHAR()
{
	int i,j;
	for(i =0 ;i<4  ; i++)
	{
		KEYPAD_PORT |= ((1<<KEYPAD_COLS[0]) | (1<<KEYPAD_COLS[1]) | (1<<KEYPAD_COLS[2]) | (1<<KEYPAD_COLS[3]));
		KEYPAD_PORT &= ~(1<<KEYPAD_COLS[i]);
		for(j=0 ; j<4 ;j++)
		{
			if(!(KEYPAD_PIN & (1<<KEYPAD_ROWS[j])))
			{
				while (!(KEYPAD_PIN & (1<<KEYPAD_ROWS[j]))); //SINGLE PRESS
				switch(i)
				{
					case (0):
					{
						if(j==0) return '7' ;
						else if(j==1) return '4';
						else if(j==2) return '1';
						else if(j==3) return '?';
						
					}
					case (1):
					{
						if(j==0) return '8' ;
						else if(j==1) return '5';
						else if(j==2) return '2';
						else if(j==3) return '0';
						
					}
					
					
					case (2):
					{
						if(j==0) return '9' ;
						else if(j==1) return '6';
						else if(j==2) return '3';
						else if(j==3) return '=';
						
					}
					
					case (3):
					{
						if(j==0) return '/' ;
						else if(j==1) return '*';
						else if(j==2) return '-';
						else if(j==3) return '+';
						
					}
					
					
				}
				
				
			}
		}
	}
	return 'A';
}