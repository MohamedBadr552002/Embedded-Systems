/*
 * LCD.c
 *
 *  Created on: Feb 16, 2023
 *      Author: Mohamed
 */


#include "LCD.h"


 void LCD_delay(int ms){
	volatile uint32_t counter =0;
	for(int i =0;i<ms;i++){
		for(;counter<1500;counter++);
	}
}
//void MCAL_GPIO_WritePin(GPIO_TypeDef * GPIOx,uint16_t PinNumber,uint8_t Vlaue);

void LCD_kick(s_LCD_Config_t  * LCD){
	//BITSET(*(LCD->s_LCDCtrlPins.p_PortReg),LCD->s_LCDCtrlPins.enpin);									//enable pulse
	MCAL_GPIO_Writepin(LCD->s_LCDCtrlPins.GPIOX,LCD->s_LCDCtrlPins.enpin,GPIO_PIN_SET);
	LCD_delay(1);
	MCAL_GPIO_Writepin(LCD->s_LCDCtrlPins.GPIOX,LCD->s_LCDCtrlPins.enpin,GPIO_PIN_RESET);

}

/*************************************
 * @brief Initialize the LCD module.
 *
 * This function initializes the LCD module based on the provided configuration.
 *
 * @param LCD Pointer to the LCD configuration structure.
 *************************************/
void HAL_LCD_init(s_LCD_Config_t  *  LCD ){
	//*(LCD->s_LCDCtrlPins.p_DataDireReg) |= (1<<LCD->s_LCDCtrlPins.enpin) | (1<<LCD->s_LCDCtrlPins.rspin) | (1<<LCD->s_LCDCtrlPins.rwpin);
	GPIO_pinConfig_t pin = {LCD->s_LCDCtrlPins.enpin ,GPIO_MODE_OUTPUT_PP, GPIO_SPEED_10M};
	MCAL_GPIO_Init(LCD->s_LCDCtrlPins.GPIOX,&pin);
	pin.GPIO_PIN_NUMBER = LCD->s_LCDCtrlPins.rspin;
	MCAL_GPIO_Init(LCD->s_LCDCtrlPins.GPIOX,&pin);
	LCD->Ch_Counter = 0;
	if(LCD->e_OperMode < EIGHTBIT_1LINE_7DOT)	// 4 bits
	{
		//*(LCD->s_LCDDataPins.p_DataDireReg) |= (0x0F << LCD->s_LCDDataPins.DataPinStart);
		for(uint8_t i =0;i<4;i++){
			pin.GPIO_PIN_NUMBER = LCD->s_LCDDataPins.DataPinStart << i;
			MCAL_GPIO_Init(LCD->s_LCDDataPins.GPIOX,&pin);
		}
	}
	else
	{
		for(uint8_t i =0;i<8;i++){
			pin.GPIO_PIN_NUMBER = LCD->s_LCDDataPins.DataPinStart << i;
			MCAL_GPIO_Init(LCD->s_LCDDataPins.GPIOX,&pin);
		}
	}
	HAL_LCD_sendchar(LCD ,RETURN_HOME , COMMAND );
	HAL_LCD_sendchar(LCD ,FUNCTION_SET + LCD->e_OperMode , COMMAND );
	HAL_LCD_sendchar(LCD ,DISPLAY_CONTROL + LCD->e_DispCtrl , COMMAND );
	HAL_LCD_sendchar(LCD ,ENTRY_MODE_SET + LCD->e_EntryMode , COMMAND );
	HAL_LCD_clearscreen(LCD);
	LCD_returnhome(LCD);
	HAL_LCD_sendchar(LCD ,SET_DD_ADDRESS , COMMAND );
}

/**
 * @brief Display a character or send a command to the LCD.
 *
 * This function sends a character or a command to the LCD module based on the
 * specified character type (data or command).
 *
 * @param LCD Pointer to the LCD configuration structure.
 * @param data The character or command to be sent to the LCD.
 * @param e_LCDCharType Character type (DATA or COMMAND).
 */
void HAL_LCD_sendchar(s_LCD_Config_t  *  LCD ,unsigned char data ,e_LCDCharType_t e_LCDCharType)
{
	LCDIsbusy(LCD);
	if(LCD->e_OperMode < EIGHTBIT_1LINE_7DOT)	// 4 bits
	{
		//void MCAL_GPIO_WriteGroup(GPIO_TypeDef * GPIOx,uint16_t Vlaue,uint16_t mask);
		//*(LCD->s_LCDDataPins.p_PortReg) &= ~(0x0F << LCD->s_LCDDataPins.DataPinStart);						// clear the data pins
		//*(LCD->s_LCDDataPins.p_PortReg) = (((data & 0xF0) >> 4) << LCD->s_LCDDataPins.DataPinStart);		//the high nibble
		MCAL_GPIO_WriteGroup(
				LCD->s_LCDDataPins.GPIOX
				,((data & 0xF0) >> 4)*LCD->s_LCDDataPins.DataPinStart
				,0x0F*LCD->s_LCDDataPins.DataPinStart);
		if(e_LCDCharType == COMMAND)
			//BITCLEAR(*(LCD->s_LCDCtrlPins.p_PortReg),LCD->s_LCDCtrlPins.rspin);
			MCAL_GPIO_Writepin(LCD->s_LCDCtrlPins.GPIOX,LCD->s_LCDCtrlPins.rspin,GPIO_PIN_RESET);
		else{
			//BITSET(*(LCD->s_LCDCtrlPins.p_PortReg),LCD->s_LCDCtrlPins.rspin);
			MCAL_GPIO_Writepin(LCD->s_LCDCtrlPins.GPIOX,LCD->s_LCDCtrlPins.rspin,GPIO_PIN_SET);
		}

		LCD_kick(LCD);

		//*(LCD->s_LCDDataPins.p_PortReg) &= ~(0x0F << LCD->s_LCDDataPins.DataPinStart);
		//*(LCD->s_LCDDataPins.p_PortReg) |= ((data & 0x0F) << LCD->s_LCDDataPins.DataPinStart);
		MCAL_GPIO_WriteGroup(LCD->s_LCDDataPins.GPIOX
				,(data & 0x0F)*LCD->s_LCDDataPins.DataPinStart
				,0x0F*LCD->s_LCDDataPins.DataPinStart);

		LCD_kick(LCD);
		LCD_delay(1);
	}
	else
	{						//8bit mode
		//*(LCD->s_LCDDataPins.p_PortReg) &= ~(0xFF << LCD->s_LCDDataPins.DataPinStart);
		//*(LCD->s_LCDDataPins.p_PortReg) |= (data << LCD->s_LCDDataPins.DataPinStart);
		MCAL_GPIO_WriteGroup(LCD->s_LCDDataPins.GPIOX
				,(data & 0xFF)*LCD->s_LCDDataPins.DataPinStart
				,0xFF*LCD->s_LCDDataPins.DataPinStart);
		if(e_LCDCharType == COMMAND)
			//BITCLEAR(*(LCD->s_LCDCtrlPins.p_PortReg),LCD->s_LCDCtrlPins.rspin);
			MCAL_GPIO_Writepin(LCD->s_LCDCtrlPins.GPIOX,LCD->s_LCDCtrlPins.rspin,GPIO_PIN_RESET);
		else{
			//BITSET(*(LCD->s_LCDCtrlPins.p_PortReg),LCD->s_LCDCtrlPins.rspin);
			MCAL_GPIO_Writepin(LCD->s_LCDCtrlPins.GPIOX,LCD->s_LCDCtrlPins.rspin,GPIO_PIN_SET);

		}
		LCD_kick(LCD);
	}
	if(e_LCDCharType == DATA){
		LCD->Ch_Counter ++;
		if(LCD->Ch_Counter==LINE_DIGITS)
			LCD_gotoxy(LCD,0,1);
		else if (LCD->Ch_Counter==2*LINE_DIGITS)
			LCD_gotoxy(LCD,0,2);
		else if (LCD->Ch_Counter==3*LINE_DIGITS)
			LCD_gotoxy(LCD,0,3);
	}
}

/**
 * @brief Display a string on the LCD.
 *
 * This function displays the whole string on the LCD module.
 *
 * @param LCD Pointer to the LCD configuration structure.
 * @param data The string to be displayed on the LCD.
 */
void HAL_LCD_sendstring(s_LCD_Config_t  * LCD , const char *  data)
{
	for(;*data != '\0';data++){
		HAL_LCD_sendchar(LCD,*data,DATA);
	}
}

/**
 * @brief Check the busy flag of the LCD.
 *
 * This function checks the busy flag of the LCD to determine if the LCD is busy
 * processing a command.
 *
 * @note This function may not work in 4-bit mode.
 *
 * @param LCD Pointer to the LCD configuration structure.
 */
void LCDIsbusy(s_LCD_Config_t  * LCD)
{
	//currently I'm working on reading the actual busy flag
	//for the end of the dev process xD let it simply a delay.
	LCD_delay(1);
}
/**
 * @brief Clear the LCD screen.
 *
 * This function clears the entire content of the LCD screen.
 *
 * @param LCD Pointer to the LCD configuration structure.
 */
void HAL_LCD_clearscreen(s_LCD_Config_t  * LCD)
{
	HAL_LCD_sendchar(LCD , ClEAR_SCREEN , COMMAND );
	LCD->Ch_Counter=0;
}
/**
 * @brief Return the cursor to the home position (0, 0).
 *
 * This function moves the cursor to the home position (0, 0) of the LCD.
 *
 * @param LCD Pointer to the LCD configuration structure.
 */
void LCD_returnhome(s_LCD_Config_t  * LCD)
{
	HAL_LCD_sendchar(LCD , RETURN_HOME , COMMAND );
	LCD->Ch_Counter=0;
}
/**
 * @brief Move the cursor to the specified position.
 *
 * This function moves the cursor to the specified position on the LCD.
 *
 * @param LCD Pointer to the LCD configuration structure.
 * @param x The column position (0 to 15).
 * @param y The row position (0 or 1 for two-line LCD).
 */
void LCD_gotoxy(s_LCD_Config_t  * LCD , unsigned char x , unsigned char y)
{
	uint32_t address;
	switch (y)
	{
	case 0:
		address = x;
		break;
	case 1:
		address = 0x40 + x;
		break;
	case 2:
		address = 0x10 + x; // For line 3, use 0x10 to 0x1F addresses
		break;
	case 3:
		address = 0x50 + x; // For line 4, use 0x50 to 0x5F addresses
		break;
	}
	LCD->Ch_Counter=y*LINE_DIGITS+x;
	HAL_LCD_sendchar(LCD,SET_DD_ADDRESS+address,COMMAND);
}
/**
 * @brief Build a custom character for the LCD.
 *
 * This function builds a custom character at the specified location in the LCD
 * character generator RAM. The custom character can later be displayed on the LCD.
 *
 * @param LCD Pointer to the LCD configuration structure.
 * @param location The location (0 to 7) to store the custom character.
 * @param pattern Pointer to the pattern data for the custom character.
 */
void LCD_buildcustom(s_LCD_Config_t  * LCD ,unsigned char location ,const unsigned char * pattern )
{
	unsigned char i=0;
	if(location<8){
		HAL_LCD_sendchar(LCD,0x40+(location*8),COMMAND);
		for(i=0;i<8;i++)
			HAL_LCD_sendchar(LCD,pattern[ i ],DATA);
	}
}
/**
 * @brief Display a custom character on the LCD.
 *
 * This function displays a custom character stored in the character generator RAM
 * at the specified location on the LCD.
 *
 * @param LCD Pointer to the LCD configuration structure.
 * @param location The location (0 to 7) of the custom character in the character generator RAM.
 */
void LCD_dispcustom(s_LCD_Config_t  * LCD ,unsigned char location){
	HAL_LCD_sendchar(LCD,location,DATA);
}
/**
 * @brief Shift the display and/or cursor.
 *
 * This function shifts the display and/or cursor to the left or right based on the specified direction.
 *
 * @param LCD Pointer to the LCD configuration structure.
 * @param e_ShiftDir Shift direction for the display and/or cursor.
 */
void LCD_shift(s_LCD_Config_t  * LCD ,e_ShiftDir_t e_ShiftDir){
	HAL_LCD_sendchar(LCD ,CURSOR_DISPLAY_SHIFT + e_ShiftDir , COMMAND );
}

void Wait()
{
	int i=0;
	for(i=0;i<25000;i++);
}
