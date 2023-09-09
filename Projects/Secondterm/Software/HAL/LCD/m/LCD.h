/*
 * LCD.h
 *
 *  Created on: Feb 16, 2023
 *      Author: Mohamed
 */

#ifndef INCLUDES_LCD_H_
#define INCLUDES_LCD_H_

#include "stm32f103c6.h"
#include "STM32F103C6_DRIVER_GPIO.h"

#define LINE_DIGITS 16

/**
 * @brief Enumeration for the shift direction of the LCD.
 *
 * This enumeration defines the possible shift directions for the LCD display and cursor.
 */
typedef enum{
    CURSOR_LEFT  = 0x00, /**< Shift the cursor to the left. */
    CURSOR_RIGHT = 0x04, /**< Shift the cursor to the right. */
    DISP_LEFT    = 0x08, /**< Shift the entire display to the left. */
    DISP_RIGHT   = 0x0c  /**< Shift the entire display to the right. */
} e_ShiftDir_t;

/**
 * @brief Enumeration for the entry mode of the LCD.
 *
 * This enumeration defines the possible entry modes for the LCD.
 */
typedef enum{
    NOSHIFT_DECREMENT = 0, /**< Entry mode: No shift and decrement cursor position. */
    SHIFT_DECREMENT   = 1, /**< Entry mode: Shift cursor to the left and decrement cursor position. */
    NOSHIFT_INCREMENT = 2, /**< Entry mode: No shift and increment cursor position. */
    SHIFT_INCREMENT   = 3  /**< Entry mode: Shift cursor to the right and increment cursor position. */
} e_EntryMode_t;

/**
 * @brief Enumeration for the display control of the LCD.
 *
 * This enumeration defines the possible display control options for the LCD.
 */
typedef enum{
    OFFDISP_OFFCURSOR    = 0x00, /**< Display off, cursor off. */
    ONDISP_OFFCURSOR     = 0x04, /**< Display on, cursor off. */
    ONDISP_ONCURSOR      = 0x06, /**< Display on, cursor on. */
    ONDISP_BLINKCURSOR   = 0x07  /**< Display on, cursor blinking. */
} e_DispCtrl_t;

/**
 * @brief Enumeration for the operating mode of the LCD.
 *
 * This enumeration defines the possible operating modes (data length and lines) for the LCD.
 */
typedef enum{
    FOURBIT_1LINE_7DOT    = 0x00, /**< 4-bit data, 1-line display, 5x7 dot character font. */
    FOURBIT_1LINE_10DOT   = 0x04, /**< 4-bit data, 1-line display, 5x10 dot character font. */
    FOURBIT_2LINE_7DOT    = 0x08, /**< 4-bit data, 2-line display, 5x7 dot character font. */
    FOURBIT_2LINE_10DOT   = 0x0C, /**< 4-bit data, 2-line display, 5x10 dot character font. */
    EIGHTBIT_1LINE_7DOT   = 0x10, /**< 8-bit data, 1-line display, 5x7 dot character font. */
    EIGHTBIT_1LINE_10DOT  = 0x14, /**< 8-bit data, 1-line display, 5x10 dot character font. */
    EIGHTBIT_2LINE_7DOT   = 0x18, /**< 8-bit data, 2-line display, 5x7 dot character font. */
    EIGHTBIT_2LINE_10DOT  = 0x1C  /**< 8-bit data, 2-line display, 5x10 dot character font. */
} e_OperMode_t;

/**
 * @brief Data structure for the data pins of the LCD.
 *
 * This structure defines the GPIO port and the starting pin number
 * for the data pins of the LCD.
 */
typedef struct {
	GPIO_typeDef *GPIOX;    /**< GPIO port for the data pins. */
    uint16_t DataPinStart;  /**< The pin number of the lowest data pin. */
} s_LCDDataPins_t;

/**
 * @brief Data structure for the control pins of the LCD.
 *
 * This structure defines the GPIO port and the pin numbers for the
 * register select (RS) pin and the enable (EN) pin of the LCD.
 */
typedef struct {
	GPIO_typeDef *GPIOX;    /**< GPIO port for the control pins. */
    uint16_t rspin;         /**< Register select (RS) pin number. */
    uint16_t enpin;         /**< Enable (EN) pin number. */
} s_LCDCtrlPins_t;

/**
 * @brief Configuration structure for the LCD module.
 *
 * This structure holds the configuration parameters for the LCD module.
 */
typedef struct {
    s_LCDCtrlPins_t s_LCDCtrlPins; /**< Control pins configuration. */
    s_LCDDataPins_t s_LCDDataPins; /**< Data pins configuration. */
    e_EntryMode_t e_EntryMode;     /**< Entry mode configuration. */
    e_DispCtrl_t e_DispCtrl;       /**< Display control configuration. */
    e_OperMode_t e_OperMode;       /**< Operating mode (data length and lines) configuration. */
    uint8_t Ch_Counter;            /**< Internal character counter. */
} s_LCD_Config_t;

/**
 * @brief Enumeration for the type of character to be sent to the LCD.
 *
 * This enumeration defines the possible types of characters that can be sent to the LCD,
 * either a command or data (character to be displayed).
 */
typedef enum {
    COMMAND, /**< The character to be sent is a command to the LCD. */
    DATA     /**< The character to be sent is data to be displayed on the LCD. */
} e_LCDCharType_t;

/**
 * @brief Admin LCD configuration for the LCD module.
 *
 * This variable represents the admin LCD's configuration that's used to initialize the admin LCD
 * @note You must not edit this variable.
 */
extern s_LCD_Config_t LCD_admin;

/**
 * @brief Entry configuration for the LCD module.
 *
 * This variable represents the entry gate LCD's configuration to initialize the entry gate LCD
 * @note You must not edit this variable.
 *
 */
extern s_LCD_Config_t LCD_user;


//--------------------------------------------------
//=========================APIS=====================
//--------------------------------------------------

void HAL_LCD_init(s_LCD_Config_t *LCD);

void HAL_LCD_sendchar(s_LCD_Config_t *LCD, unsigned char data, e_LCDCharType_t e_LCDCharType);

void HAL_LCD_sendstring(s_LCD_Config_t *LCD, const char *data);

void HAL_LCD_clearscreen(s_LCD_Config_t *LCD);

void LCDIsbusy(s_LCD_Config_t *LCD);


//-----------------------------------------------------------------
//========================= Generic Functions =====================
//-----------------------------------------------------------------

void LCD_returnhome(s_LCD_Config_t *LCD);

void LCD_gotoxy(s_LCD_Config_t *LCD, unsigned char x, unsigned char y);

void LCD_buildcustom(s_LCD_Config_t *LCD, unsigned char location, const unsigned char *pattern);

void LCD_dispcustom(s_LCD_Config_t *LCD, unsigned char location);

void LCD_shift(s_LCD_Config_t *LCD, e_ShiftDir_t e_ShiftDir);



#define BITSET(reg,bit) 		(reg |=(1<< bit))
#define BITCLEAR(reg,bit) 		(reg &= ~(1<<bit))
#define ClEAR_SCREEN			0x01
#define RETURN_HOME				0x02
#define ENTRY_MODE_SET			0x04
#define	DISPLAY_CONTROL			0x08
#define CURSOR_DISPLAY_SHIFT	0x10
#define FUNCTION_SET			0x20
#define SET_CG_ADDRESS			0x40
#define SET_DD_ADDRESS			0x80






#endif /* INCLUDES_LCD_H_ */
