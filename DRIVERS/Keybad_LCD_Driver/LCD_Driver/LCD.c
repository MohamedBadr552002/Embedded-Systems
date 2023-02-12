/*
 * LCD.c
 *
 * Created: 11/30/2022 4:35:08 PM
 *  Author: Mohamed
 */ 
#include "LCD.h"

void LCD_KICK()
{
	LCD_CTRL &=~(1<<ENABLE_SWITCH);
	_delay_ms(30);
	LCD_CTRL |=(1<<ENABLE_SWITCH);
}
void LCD_ISBUSY()
{
	DataDir_LCD_PORT &= ~(0xFF << DATA_SHIFT);
	LCD_CTRL |=(1<<RW_SWITCH);  //read mode
	LCD_CTRL &=~(1<<RS_SWITCH);
	LCD_KICK();
	
	DataDir_LCD_PORT =0xFF;
	LCD_CTRL &=~(1<<RS_SWITCH);
}

void LCD_GOTO_NEXT_LINE(int line ,int posision)
{
	if(line ==1)
	{	
		if (posision >16 && posision<=0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FRIST_ROW + posision); 
		}
			
	}
	else if (line == 2)
	{	
		if (posision >32 && posision <=0)
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
{	_delay_ms(20);
	LCD_ISBUSY();
	DataDir_LCD_CTRL |= (1<<ENABLE_SWITCH) | (1<<RW_SWITCH) | (1<<RS_SWITCH);
	LCD_CTRL &= ~((1<<ENABLE_SWITCH) | (1<<RW_SWITCH) | (1<<RS_SWITCH));
	DataDir_LCD_PORT =0xFF;
	LCD_clear_screen();
	
	#ifdef EIGHT_BIT_MODE
		LCD_WRITE_COMMAND(0x02);
		LCD_WRITE_COMMAND(LCD_Function_Set_8BIT_2LINES);
	#endif
	
	#ifdef FOUR_BIT_MODE
	LCD_ISBUSY();
	LCD_WRITE_COMMAND(LCD_Function_Set_4BIT_2LINES);
	#endif
	
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FRIST_ROW);
	LCD_WRITE_COMMAND(LCD_DIS_ON_CURSOR_BLINK);
	
	
}

void LCD_WRITE_COMMAND(unsigned char command)
{	
	LCD_ISBUSY();
	#ifdef EIGHT_BIT_MODE
		LCD_PORT = command;
		LCD_CTRL &= ~((1<<RW_SWITCH) | (1<<RS_SWITCH));
		_delay_ms(1);
		LCD_KICK();
	#endif FOUR_BIT_MODE
		
		
	#ifdef FOUR_BIT_MODE
		LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
		LCD_CTRL &= ~((1<<RW_SWITCH) | (1<<RS_SWITCH));
		_delay_ms(1);
		LCD_KICK();
		LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
		LCD_CTRL &= ~((1<<RW_SWITCH) | (1<<RS_SWITCH));
		_delay_ms(1);
		LCD_KICK();
	#endif
}
void LCD_WRITE_CHAR(unsigned char data)
{	
	LCD_ISBUSY();
	#ifdef EIGHT_BIT_MODE	
	LCD_PORT = data;
	LCD_CTRL &= ~(1<<RW_SWITCH);
	LCD_CTRL |=(1<<RS_SWITCH);
	_delay_ms(1);
	LCD_KICK();
	#endif
	
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
	
	#endif
	
}

void LCD_WRITE_STRING(char* data)
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