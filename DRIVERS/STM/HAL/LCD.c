/*
 * LCD.c
 *
 *  Created on: Feb 16, 2023
 *      Author: Mohamed
 */


#include "LCD.h"



GPIO_pinConfig_t *P_Config;


void IS_LCD_Busy()
{
#ifdef Eight_Bit_MODE
	//Setting LCD PORT As Input FLO
	P_Config ->GPIO_PIN_NUMBER = GPIO_PIN0;
	P_Config ->GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA, P_Config);

	P_Config ->GPIO_PIN_NUMBER = GPIO_PIN1;
	P_Config ->GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA, P_Config);

	P_Config ->GPIO_PIN_NUMBER = GPIO_PIN2;
	P_Config ->GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA, P_Config);

	P_Config ->GPIO_PIN_NUMBER = GPIO_PIN3;
	P_Config ->GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA, P_Config);

	P_Config ->GPIO_PIN_NUMBER = GPIO_PIN4;
	P_Config ->GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA, P_Config);

	P_Config ->GPIO_PIN_NUMBER = GPIO_PIN5;
	P_Config ->GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA, P_Config);

	P_Config ->GPIO_PIN_NUMBER = GPIO_PIN6;
	P_Config ->GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA, P_Config);

	P_Config ->GPIO_PIN_NUMBER = GPIO_PIN7;
	P_Config ->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_Init(GPIOA, P_Config);

#endif
#ifdef FOUR_Bit_MODE
	DataDir_LCD_PORT |=(0xff<< Data_Shift);
#endif
	//Setting Control in Read Mode
	MCAL_GPIO_Writepin(GPIOA,RW_Switch , GPIO_PIN_SET);
	//Rs Is off in Command Mode
	MCAL_GPIO_Writepin(GPIOA,RS_Switch , GPIO_PIN_RESET);
	//while(LCD_PORT >= 0x80);
	//RS IS ON
	MCAL_GPIO_Writepin(GPIOA,RS_Switch , GPIO_PIN_SET);
}
void LCD_Send_Pulse()
{
	MCAL_GPIO_Writepin(LCD_CTRL,EN_Switch,GPIO_PIN_SET);
//	LCD_CTRL &=~(1<<EN_Switch);
    wait_ms(50);

    MCAL_GPIO_Writepin(LCD_CTRL, EN_Switch, GPIO_PIN_RESET);
//	LCD_CTRL |= (1<<EN_Switch);
}
void LCD_Init()
{

	//Making EN_Switch pin as output PP with zero as initial state
	P_Config ->GPIO_PIN_NUMBER = EN_Switch;
	P_Config ->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	P_Config ->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_CTRL, P_Config);

	//Making RS_Switch pin as output PP with zero as initial state
	P_Config ->GPIO_PIN_NUMBER = RS_Switch;
	P_Config ->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	P_Config ->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_CTRL, P_Config);

	//Making RW_Switch pin as output PP with zero as initial state
	P_Config ->GPIO_PIN_NUMBER = RW_Switch;
	P_Config ->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	P_Config ->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_CTRL, P_Config);

#ifdef Eight_Bit_MODE
	//Setting LCD PORT as OUTPUT for A0 to A7
	P_Config ->GPIO_PIN_NUMBER = GPIO_PIN0;
	P_Config ->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	P_Config ->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_CTRL, P_Config);

	P_Config ->GPIO_PIN_NUMBER = GPIO_PIN1;
	P_Config ->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	P_Config ->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_CTRL, P_Config);

	P_Config ->GPIO_PIN_NUMBER = GPIO_PIN2;
	P_Config ->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	P_Config ->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_CTRL, P_Config);

	P_Config ->GPIO_PIN_NUMBER = GPIO_PIN3;
	P_Config ->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	P_Config ->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_CTRL, P_Config);

	P_Config ->GPIO_PIN_NUMBER = GPIO_PIN4;
	P_Config ->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	P_Config ->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_CTRL,P_Config);

	P_Config ->GPIO_PIN_NUMBER = GPIO_PIN5;
	P_Config ->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	P_Config ->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_CTRL, P_Config);

	P_Config ->GPIO_PIN_NUMBER = GPIO_PIN6;
	P_Config ->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	P_Config ->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_CTRL, P_Config);

	P_Config ->GPIO_PIN_NUMBER = GPIO_PIN7;
	P_Config ->GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	P_Config ->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_CTRL, P_Config);

	wait_ms(15);
	LCD_Clear_Screen();
	LCD_Send_Command(LCD_8bit_2Line);
#endif



#ifdef FOUR_Bit_MODE
	DataDir_LCD_PORT |= 0x0f;
	wait_ms(15);
	LCD_Clear_Screen();
	LCD_Send_Command(0x02);
	LCD_Send_Command(LCD_4bit_2_Line);
#endif



	LCD_Send_Command(LCD_Entry_Mode);
	LCD_Send_Command(LCD_Start_At_Beginning_Of_First_Line);
	LCD_Send_Command(LCD_Display_Cursor_Blinking);

}
void LCD_Send_Command (unsigned char CMD)
{
#ifdef Eight_Bit_MODE
	//IS_LCD_Busy();

	MCAL_GPIO_Writeport(LCD_PORT, CMD);
	MCAL_GPIO_Writepin(GPIOA,RS_Switch, GPIO_PIN_RESET);
	MCAL_GPIO_Writepin(GPIOA, RW_Switch, GPIO_PIN_RESET);
	wait_ms(20);
	LCD_Send_Pulse();
#endif
#ifdef FOUR_Bit_MODE
	IS_LCD_Busy();
	LCD_PORT =  ((LCD_PORT & 0x0F) | (CMD & 0xF0));
	//Rs is off at CMD  Mode And RW is off
	LCD_CTRL =~((1<<RS_Switch)|(1<<RW_Switch));
	//Sending MSB Nibble
	LCD_Send_Pulse();
	LCD_PORT = ((LCD_PORT & 0x0F) | (CMD << Data_Shift)) ;
	//Rs is off at CMD  Mode And RW is off
	LCD_CTRL =~((1<<RS_Switch)|(1<<RW_Switch));
	//Sending LSB Nibble
	LCD_Send_Pulse();
#endif
}
void LCD_Send_A_Character(unsigned char data)
{
	//IS_LCD_Busy();
#ifdef Eight_Bit_MODE
	//Putting Data on PORT
	MCAL_GPIO_Writeport(LCD_PORT, data);
	//Rs is on at Data mode

	MCAL_GPIO_Writepin(GPIOA, RS_Switch, GPIO_PIN_SET);
	//Rw is off at Data mode

	MCAL_GPIO_Writepin(GPIOA, RW_Switch, GPIO_PIN_RESET);
	//Sending Data
	wait_ms(20);
	LCD_Send_Pulse();
#endif
#ifdef FOUR_Bit_MODE
	//Putting MSB Nibble on PORT
	LCD_PORT = (LCD_PORT & 0x0F)|(data & 0xF0);
	//RS is on at read mode
	LCD_CTRL |= (1<<RS_Switch);
	//RW is off at read mode
	LCD_CTRL &= ~(1<<RW_Switch);
	//Send MSB NIbble
	LCD_Send_Pulse();
	//Putting LSB Nibble on Port
	LCD_PORT =(LCD_PORT & 0x0F)|(data << Data_Shift);
	//RS is on at read mode
	LCD_CTRL |= (1<<RS_Switch);
	//RW is off at read mode
	LCD_CTRL &= ~(1<<RW_Switch);
	//Send MSB NIbble
	LCD_Send_Pulse();
#endif
}
void LCD_Send_A_String(char * str)
{
	int i ;
	for(i=0;str[i] != '\0' ; i++)
	{
		LCD_Send_A_Character(str[i]);
		if(i==16)
		{
			LCD_Goto_XY(2,1);
		}
		else if ( i == 32)
		{
			LCD_Clear_Screen();
			LCD_Goto_XY(1,1);
		}
	}

}
void LCD_Goto_XY(unsigned char row , unsigned char column)
{
	if(row == 1)
	{
		if(column > 0 && column < 16 )
			LCD_Send_Command(LCD_Start_At_Beginning_Of_First_Line+column);
	}
	else if( row == 2)
	{
		if(column > 0 && column < 16 )
			LCD_Send_Command(LCD_Start_At_Beginning_Of_Second_Line+column);
	}
}


void LCD_Clear_Screen()
{
	LCD_Send_Command(LCD_Clear_SCREEN);
}
