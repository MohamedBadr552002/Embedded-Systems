/*
 * keypad.c
 *
 *  Created on: Feb 16, 2023
 *      Author: Mohamed
 */

#include "keypad.h"


GPIO_pinConfig_t *pin_cfg ;

int KEYPAD_ROWS[] ={R0 ,R1 ,R2 ,R3};
int KEYPAD_COLS[] ={C0 ,C1 ,C2 ,C3};

void KEYPAD_INIT()
{
	pin_cfg->GPIO_PIN_NUMBER = R0 ;
	pin_cfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pin_cfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT, pin_cfg);

	pin_cfg->GPIO_PIN_NUMBER = R1 ;
	pin_cfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pin_cfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT, pin_cfg);

	pin_cfg->GPIO_PIN_NUMBER = R2 ;
	pin_cfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pin_cfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT, pin_cfg);

	pin_cfg->GPIO_PIN_NUMBER = R3 ;
	pin_cfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pin_cfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT, pin_cfg);

	pin_cfg->GPIO_PIN_NUMBER = C0 ;
	pin_cfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pin_cfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT, pin_cfg);

	pin_cfg->GPIO_PIN_NUMBER = C1 ;
	pin_cfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pin_cfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT, pin_cfg);

	pin_cfg->GPIO_PIN_NUMBER = C2 ;
	pin_cfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pin_cfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT, pin_cfg);

	pin_cfg->GPIO_PIN_NUMBER = C3 ;
	pin_cfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pin_cfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT, pin_cfg);


	MCAL_GPIO_Writeport(KEYPAD_PORT, 0xFF);
}

char KEYPAD_GETCHAR()
{
	int i,j;
	for(i =0 ;i<4  ; i++)
	{
		MCAL_GPIO_Writepin(KEYPAD_PORT, KEYPAD_COLS[0], GPIO_PIN_SET);
		MCAL_GPIO_Writepin(KEYPAD_PORT, KEYPAD_COLS[1], GPIO_PIN_SET);
		MCAL_GPIO_Writepin(KEYPAD_PORT, KEYPAD_COLS[2], GPIO_PIN_SET);
		MCAL_GPIO_Writepin(KEYPAD_PORT, KEYPAD_COLS[3], GPIO_PIN_SET);
		MCAL_GPIO_Writepin(KEYPAD_PORT, KEYPAD_COLS[i], GPIO_PIN_RESET);
		for(j=0 ; j<4 ;j++)
		{

			if(MCAL_GPIO_Readpin(KEYPAD_PORT, KEYPAD_ROWS[j]) == 0)
			{

				while (MCAL_GPIO_Readpin(KEYPAD_PORT, KEYPAD_ROWS[j]) == 0); //SINGLE PRESS
				switch(i)
				{
					case (0):
					{
						if(j==0) return '7' ;
						else if(j==1) return '4';
						else if(j==2) return '1';
						else if(j==3) return '?';
						break ;

					}
					case (1):
					{
						if(j==0) return '8' ;
						else if(j==1) return '5';
						else if(j==2) return '2';
						else if(j==3) return '0';
						break ;
					}


					case (2):
					{
						if(j==0) return '9' ;
						else if(j==1) return '6';
						else if(j==2) return '3';
						else if(j==3) return '=';
						break ;
					}

					case (3):
					{
						if(j==0) return '/' ;
					    else if(j==1) return '*';
						else if(j==2) return '-';
						else if(j==3) return '+';
						break ;
					}


				}


			}
		}
	}
	return 'A';
}
