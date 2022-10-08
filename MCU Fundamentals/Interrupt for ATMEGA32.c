/*
 * main.c
 *
 *  Created on: Oct 8, 2022
 *      Author: Mohamed
 */

#define F_CPU 8000000ul

typedef volatile unsigned int vuint32_t ;

#define IO_BASE 0x20    // base address
#define MCUCR   *(vuint32_t *)((IO_BASE)+0x35)    //control interrupt(0,1) sense
#define MCUCSR  *(vuint32_t *)((IO_BASE)+0x34)    //control interrupt2 sense

//enable intrrupts
#define GICR  *(vuint32_t *)((IO_BASE)+0x3B)  // general interrupt control register

//handling the interrupts
#define GIFR  *(vuint32_t *)((IO_BASE)+0x3A) //general interrupt flag register


#define SREG  *(vuint32_t *)((IO_BASE)+0x3F) //the AVR status register

//for output leds
#define IO_DDRD  *(vuint32_t *)((IO_BASE)+0x11)
#define IO_portD  *(vuint32_t *)((IO_BASE)+0x12)



void main(void)
{
    // MAKE PINS 5,6,7, OUTPUT
    IO_DDRD |= 0b111<5;

    //enable the global interrupt register
    SREG |= 1<<7;

    //make interrupt 0 for any logical change
    MCUCR |= 0b01<<0;

    //make interrupt 1 for  raising edge
    MCUCR |= 0b11<<2;

    //make interrupt 2 for  failling edge
    MCUCSR |= 0<<6;

    //enable interrupt 0
    GICR |= 1<<6;

    //enable interrupt 1
    GICR |= 1<<7;

    //enable interrupt 2
    GICR |= 1<<5;

    while(1)
    {
        //clear pins
        IO_portD |= 0<<5;
        IO_portD |= 0<<6;
        IO_portD |= 0<<7;


    }





}


void ISR0(void)
{

    //turn on led on pin5
    IO_portD |= 1<<5;

    for (volatile int i =0 ;i<200000;i++);

    GIFR |= 1<<6;

}

void ISR1(void)
{
    //turn on led on pin5
    IO_portD |= 1<<6;

    for (volatile int i =0 ;i<200000;i++);


    GIFR |= 1<<7;
}

void ISR2(void)
{
    //turn on led on pin5
    IO_portD |= 1<<7;

    for (volatile int i =0 ;i<200000;i++);

    GIFR |= 1<<5;
}

