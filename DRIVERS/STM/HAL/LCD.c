/*
 * LCD.c
 *
 *  Created on: Feb 16, 2023
 *      Author: Mohamed
 */


#include "LCD.h"

GPIO_pinConfig_t *pincfg ;

void _delay_ms(uint32_t i)
{
	uint32_t x ,y ;
	for(x=0;x<i;x++)
	{
		for(y=0;y<255;y++);
	}
}


void LCD_KICK()
{
	MCAL_GPIO_Writepin(LCD_CTRL, ENABLE_SWITCH , GPIO_PIN_SET);
	_delay_ms(50);
	MCAL_GPIO_Writepin(LCD_CTRL, ENABLE_SWITCH , GPIO_PIN_RESET);
}
void LCD_ISBUSY()
{

	pincfg->GPIO_PIN_NUMBER = GPIO_PIN0 ;
	pincfg->GPIO_MODE = GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_Init(LCD_CTRL , pincfg);

	pincfg->GPIO_PIN_NUMBER = GPIO_PIN1 ;
	pincfg->GPIO_MODE = GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_Init(LCD_CTRL , pincfg);

	pincfg->GPIO_PIN_NUMBER = GPIO_PIN2 ;
	pincfg->GPIO_MODE = GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_Init(LCD_CTRL , pincfg);

	pincfg->GPIO_PIN_NUMBER = GPIO_PIN3 ;
	pincfg->GPIO_MODE = GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_Init(LCD_CTRL , pincfg);

	pincfg->GPIO_PIN_NUMBER = GPIO_PIN4 ;
	pincfg->GPIO_MODE = GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_Init(LCD_CTRL , pincfg);

	pincfg->GPIO_PIN_NUMBER = GPIO_PIN5 ;
	pincfg->GPIO_MODE = GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_Init(LCD_CTRL , pincfg);

	pincfg->GPIO_PIN_NUMBER = GPIO_PIN6 ;
	pincfg->GPIO_MODE = GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_Init(LCD_CTRL , pincfg);

	pincfg->GPIO_PIN_NUMBER = GPIO_PIN7 ;
	pincfg->GPIO_MODE = GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_Init(LCD_CTRL , pincfg);

	MCAL_GPIO_Writepin(LCD_PORT, RW_SWITCH , GPIO_PIN_SET);
	MCAL_GPIO_Writepin(LCD_PORT, RS_SWITCH , GPIO_PIN_RESET);

	LCD_KICK();

	MCAL_GPIO_Writepin(LCD_CTRL, RW_SWITCH , GPIO_PIN_RESET);
}

void LCD_GOTO_NEXT_LINE(int line ,int posision)
{
	if(line ==1)
	{
		if (posision < 16 && posision>=0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FRIST_ROW + posision);
		}

	}
	else if (line == 2)
	{
		if (posision < 16 && posision>=0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW + posision);
		}

	}
}

void LCD_clear_screen(void)
{
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}

void LCD_INIT(void)
{
	_delay_ms(20);

	pincfg->GPIO_PIN_NUMBER = ENABLE_SWITCH ;
	pincfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pincfg->GPIO_OUTPUT_SPEED =GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT , pincfg);

	pincfg->GPIO_PIN_NUMBER = RS_SWITCH ;
	pincfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pincfg->GPIO_OUTPUT_SPEED =GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT , pincfg);


	pincfg->GPIO_PIN_NUMBER = RW_SWITCH ;
	pincfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pincfg->GPIO_OUTPUT_SPEED =GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT , pincfg);

	_delay_ms(15);

	pincfg->GPIO_PIN_NUMBER = GPIO_PIN0 ;
	pincfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pincfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT , pincfg);

	pincfg->GPIO_PIN_NUMBER = GPIO_PIN1 ;
	pincfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pincfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT , pincfg);

	pincfg->GPIO_PIN_NUMBER = GPIO_PIN2 ;
	pincfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pincfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT , pincfg);

	pincfg->GPIO_PIN_NUMBER = GPIO_PIN3 ;
	pincfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pincfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT , pincfg);

	pincfg->GPIO_PIN_NUMBER = GPIO_PIN4 ;
	pincfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pincfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT , pincfg);

	pincfg->GPIO_PIN_NUMBER = GPIO_PIN5 ;
	pincfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pincfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT , pincfg);

	pincfg->GPIO_PIN_NUMBER = GPIO_PIN6 ;
	pincfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pincfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT , pincfg);

	pincfg->GPIO_PIN_NUMBER = GPIO_PIN7 ;
	pincfg->GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	pincfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT , pincfg);

	_delay_ms(15);
	LCD_clear_screen();

	#ifdef EIGHT_BIT_MODE
		//LCD_WRITE_COMMAND(0x02);
		LCD_WRITE_COMMAND(LCD_Function_Set_8BIT_2LINES);
	#endif

	#ifdef FOUR_BIT_MODE
	LCD_ISBUSY();
	LCD_WRITE_COMMAND(LCD_Function_Set_4BIT_2LINES);
	#endif

	LCD_WRITE_COMMAND(LCD_Function_Set_8BIT_2LINES);
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FRIST_ROW);
	LCD_WRITE_COMMAND(LCD_DIS_ON_CURSOR_BLINK);


}

void LCD_WRITE_COMMAND(unsigned char command)
{
	LCD_ISBUSY();
	#ifdef EIGHT_BIT_MODE
		MCAL_GPIO_Writeport(LCD_PORT, command);
		MCAL_GPIO_Writepin(LCD_CTRL, RS_SWITCH , GPIO_PIN_RESET);
		MCAL_GPIO_Writepin(LCD_CTRL, RW_SWITCH , GPIO_PIN_RESET);
		_delay_ms(1);
		LCD_KICK();
	#endif

/*
	#ifdef FOUR_BIT_MODE
		LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
		LCD_CTRL &= ~((1<<RW_SWITCH) | (1<<RS_SWITCH));
		_delay_ms(1);
		LCD_KICK();
		LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
		LCD_CTRL &= ~((1<<RW_SWITCH) | (1<<RS_SWITCH));
		_delay_ms(1);
		LCD_KICK();
	#endif */
}
void LCD_WRITE_CHAR(unsigned char data)
{
	LCD_ISBUSY();
	#ifdef EIGHT_BIT_MODE

	MCAL_GPIO_Writeport(LCD_PORT, data);
	MCAL_GPIO_Writepin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_Writepin(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);
	_delay_ms(1);
	LCD_KICK();
	#endif
/*
	#ifdef FOUR_BIT_MODE
	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);
	LCD_CTRL &= ~(1<<RW_SWITCH);
	LCD_CTRL |=(1<<RS_SWITCH);
	_delay_ms(1);
	LCD_KICK();
	LCD_PORT = (LCD_PORT & 0x0F) | (data << 4);
	LCD_CTRL &= ~(1<<RW_SWITCH);
	LCD_CTRL |=(1<<RS_SWITCH);
	_delay_ms(1);
	LCD_KICK();

	#endif */

}

void LCD_WRITE_STRING(char *data)
{
	int count =0;

	while(*data > 0)
	{
		LCD_WRITE_CHAR(*data++);
		count ++;
		if(count == 16)
		{
			LCD_GOTO_NEXT_LINE(2,0);
		}
		else if(count == 32)
		{
			LCD_clear_screen();
			LCD_GOTO_NEXT_LINE(1,0);
			count=0;
		}

	}
}

