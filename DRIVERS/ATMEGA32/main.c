/*
 * ATmega32.c
 *
 * Created: 2/23/2023 9:02:20 PM
 * Author : Mohamed
 */ 




#include "INC/DIO.h"
#include "util/delay.h"
#include "HAL/inc/LCD.h"


#define F_CPU 1000000UL

void DIO_INIT(void)
{

			

}


int main(void)
{	

	
	LCD_INIT();
	LCD_WRITE_STRING("Learn In Depth . ");
    /* Replace with your application code */
    while (1) 
    {
	
		
    }
}
