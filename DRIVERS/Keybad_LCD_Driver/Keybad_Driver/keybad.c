/*
 * keybad.c
 *
 * Created: 12/2/2022 1:39:44 AM
 *  Author: Mohamed
 */ 

#include "keybad.h"

int KEYBAD_ROWS[] ={R0 ,R1 ,R2 ,R3};
int KEYBAD_COLS[] ={C0 ,C1 ,C2 ,C3};
	
void KEYBAD_INIT()
{
	DataDir_KEYBAD_CTRL &= ~((1<<R0) | (1<<R1) | (1<<R2) | (1<<R3));
	DataDir_KEYBAD_CTRL |=  ((1<<C0) | (1<<C1) | (1<<C2) | (1<<C3));
	KEYBAD_PORT = 0xFF;
}

char KEYBAD_GETCHAR()
{
	int i,j;
	for(i =0 ;i<4  ; i++)
	{
		KEYBAD_PORT |= ((1<<KEYBAD_COLS[0]) | (1<<KEYBAD_COLS[1]) | (1<<KEYBAD_COLS[2]) | (1<<KEYBAD_COLS[3]));
		KEYBAD_PORT &= ~(1<<KEYBAD_COLS[i]);
		for(j=0 ; j<4 ;j++)
		{
			if(!(KEYBAD_PIN & (1<<KEYBAD_ROWS[i])))
			{
				while (!(KEYBAD_PIN & (1<<KEYBAD_ROWS[i]))); //SINGLE PRESS
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
