/*
 * lab2.c
 *
 * Created: 10/31/2022 9:56:25 PM
 * Author : Mohamed
 */ 
#define F_CPU 8000000UL 

typedef volatile unsigned int vuint32_t ;

#define DDRD (*(vuint32_t*) 0x31)
#define PORTD (*(vuint32_t*) 0x32)

void delay(int x)
{
	unsigned int i,j;

	for (i=0 ; i<x ;i++)
	{
		for (j=0 ;j<255;j++);
	}
}


int main(void)
{
    /* Replace with your application code */
	DDRD = 0b11110000;
	PORTD = 0x0;
    while (1) 
    {
		PORTD |=(1<<5);  //led_1 SET
		delay(1);
		PORTD &=~(1<<5); //led_1 RESET
		
		PORTD |=(1<<6);  //led_2 SET
		delay(1);
		PORTD &=~(1<<6); //led_2 RESET

		PORTD |=(1<<7);  //led_3 SET
		delay(1);
		PORTD &=~(1<<7); //led_3 RESET
		
		PORTD |=(1<<4);  //buzzer SET
		delay(1);
		PORTD &=~(1<<4); //buzzer RESET
		
		
    }
}

