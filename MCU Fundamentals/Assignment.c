/*
 * GccApplication1.c
 *
 * Created: 2/9/2023 11:49:38 PM
 * Author : Mohamed
 */ 
#define F_CPU 8000000ul
#include <util/delay.h>



typedef volatile unsigned int vuint32_t ;
#define IO_BASE   0x20
//GPIO

#define PORTD    (*(vuint32_t *)(0x32))
#define DDRD     (*(vuint32_t *)(0x31))
#define PIND     (*(vuint32_t *)(0x30))



#define READPIT(reg , bit)  ((reg>>bit) & 1)

 
void GPOI_INIT(void)
{
	//PINS 4,5,6,7 output
	DDRD   |= (1<<4);
	PORTD  |= (0<<4);
	
	DDRD   |= (1<<5);
	PORTD  |= (0<<5);
	
	DDRD   |= (1<<6);
	PORTD  |= (0<<6);
	
	DDRD   |= (1<<7);
	PORTD  |= (0<<7);
	
	//PIN 1 input
	DDRD   |= (0<<1);
	PORTD  |= (0<<1);
	
	
}




int main(void)
{	
	GPOI_INIT();
    /* Replace with your application code */
    while (1) 
    {
		if( READPIT(PIND , 1) == 1)
		{
			
			PORTD |=(1<<5);
			_delay_ms(500);
			PORTD |=(1<<6);
			_delay_ms(500);
			PORTD |=(1<<7);
			_delay_ms(500);
			PORTD |=(1<<4);
			_delay_ms(500);
			
			PORTD &= ~(1<<4);
			_delay_ms(500);
			PORTD &= ~(1<<7);
			_delay_ms(500);
			PORTD &= ~(1<<6);
			_delay_ms(500);
			PORTD &= ~(1<<5);
			_delay_ms(500);
			
			
		}
    }
}

