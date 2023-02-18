#ifndef INCLUDES_LCD_H_
#define INCLUDES_LCD_H_

#include "stm32f103c6.h"
#include "STM32F103C6_DRIVER_GPIO.h"


#define LCD_PORT			GPIOA
#define DataDir_LCD_PORT	DDRA

#define LCD_CTRL			GPIOA
#define DataDir_LCD_CTRL	PORTB

//operation modes
#define EIGHT_BIT_MODE
//#define FOUR_BIT_MODE


#define RS_SWITCH		GPIO_PIN8
#define RW_SWITCH		GPIO_PIN9
#define ENABLE_SWITCH	GPIO_PIN10
//#define DATA_SHIFT		4


#define LCD_Function_Set_8BIT_1LINES  (0x30)
#define LCD_Function_Set_8BIT_2LINES  (0x38)
#define LCD_Function_Set_4BIT_2LINES  (0x28)

#define LCD_ENTRY_MODE				  (0x06)
#define LCD_MOVE_DIS_RIGHT			  (0x1C)
#define LCD_MOVE_DIS_LEFT			  (0x18)
#define LCD_MOVE_CURSOR_RIGHT		  (0x14)
#define LCD_MOVE_CURSOR_LEFT		  (0x10)
#define LCD_DIS_OFF      			  (0x08)
#define LCD_DIS_ON_CURSOR      		  (0x0E)
#define LCD_DIS_ON_CURSOR_BLINK    	  (0x0F)
#define LCD_DIS_ON_BLINK    	      (0x0D)
#define LCD_DIS_0FF          	      (0x0C)
#define LCD_ENTRY_DEC         	      (0x04)
#define LCD_ENTRY_DEC_SHIFT   	      (0x05)
#define LCD_ENTRY_INC_				  (0x06)
#define LCD_ENTRY_INC_SHIFT			  (0x07)
#define LCD_BEGIN_AT_FRIST_ROW        (0x80)
#define LCD_BEGIN_AT_SECOND_ROW       (0xC0)
#define LCD_CLEAR_SCREEN              (0x01)


void LCD_INIT(void);
void LCD_WRITE_COMMAND(unsigned char command);
void LCD_WRITE_CHAR(unsigned char data);
void LCD_WRITE_STRING(char* data);
void LCD_ISBUSY(void);
void LCD_clear_screen(void);

#endif /* INCLUDES_LCD_H_ */
