/*
 * LCD.h
 *
 *  Created on: Feb 16, 2023
 *      Author: Mohamed
 */

#ifndef INCLUDES_LCD_H_
#define INCLUDES_LCD_H_

#define F_CPU 1000000UL
#include "stm32f103c6.h"
#include "STM32F103C6_DRIVER_GPIO.h"


#define LCD_CTRL	GPIOA
#define LCD_PORT 	GPIOA
#define RS_Switch  	GPIO_PIN8
#define RW_Switch  	GPIO_PIN9
#define EN_Switch 	 GPIO_PIN10
#define Data_Shift   									4

#define LCD_8bit_1Line        						(0x30)
#define LCD_4bit_1_Line       						(0x20)

#define LCD_8bit_2Line        						(0x38)
#define LCD_4bit_2_Line       						(0x28)
#define LCD_MOVE_Display_Right 						(0x1C)
#define LCD_MOVE_Display_Left 						(0x18)
#define LCD_Cursor_Right_By_One_Character    		(0x14)
#define LCD_Cursor_Left_By_One_Character  			(0x10)
#define LCD_Display_off_Cursor_off  				(0x08)
#define LCD_Display_Cursor_On     					(0x0E)
#define LCD_Display_Cursor_Blinking  				(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_Display_Cursor_Off    					(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_Entry_Mode        						(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_Start_At_Beginning_Of_First_Line 		(0x80)
#define LCD_Start_At_Beginning_Of_Second_Line 		(0xC0)
#define LCD_Clear_SCREEN                    		(0x01)




//Modes can be operated
#define Eight_Bit_MODE
//#define FOUR_Bit_MODE

//-----------------------




//-----------------------
void IS_LCD_Busy(void);
void LCD_Send_Pulse(void);
void LCD_Send_Command (unsigned char CMD);
void LCD_Send_A_Character (unsigned char data);
void LCD_Send_A_String(char * str);
void LCD_Init();
void LCD_Clear_Screen();
void LCD_Goto_XY(unsigned char line,unsigned char position);
void LCD_Display_Number(int Number);
void LCD_Diplay_Real_Number(double Number);
void wait_ms(uint32_t time);
#endif /* INCLUDES_LCD_H_ */
