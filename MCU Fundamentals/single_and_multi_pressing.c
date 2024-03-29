/*
 * lab1.c
 *
 *  Created on: Oct 17, 2022
 *      Author: Mohamed
 */
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stdio.h>
#include <stdlib.h>

typedef volatile unsigned int vuint32_t ;
//RCC
#define RCC_BASE    0x40021000
#define RCC_APB2ENR    *(vuint32_t*) ((RCC_BASE)+0x18)

//GPIO

//Port A
#define GPIOA_BASE    0x40010800
#define GPIOA_CRL   *(vuint32_t *)(GPIOA_BASE + 0x00)  //Port configuration register low (identifiy pins (0 --> 7) for input or output)
#define GPIOA_CRH   *(vuint32_t *)(GPIOA_BASE + 0x04)  //Port configuration register high (identifiy pins (8 --> 15) for input or output)
#define GPIOA_ODR   *(vuint32_t *)(GPIOA_BASE + 0x0C)  //Port output data register
#define GPIOA_IDR   *(vuint32_t *)(GPIOB_BASE + 0x08)

//Port B
#define GPIOB_BASE    0x40010C00
#define GPIOB_CRL   *(vuint32_t *)(GPIOB_BASE + 0x00)  //Port configuration register low (identifiy pins (0 --> 7) for input or output)
#define GPIOB_CRH   *(vuint32_t *)(GPIOB_BASE + 0x04)  //Port configuration register high (identifiy pins (8 --> 15) for input or output)
#define GPIOB_ODR   *(vuint32_t *)(GPIOB_BASE + 0x0C)  //Port output data register
#define GPIOB_IDR   *(vuint32_t *)(GPIOB_BASE + 0x08)





void clock_init()
{
    //enable clock GPIO PortA
	RCC_APB2ENR |=(1<<2);

    //enable clock GPIO PortB
	RCC_APB2ENR |=(1<<3);

}

void GPIO_init()
{

	GPIOA_CRL = 0x0;
	GPIOB_CRL = 0x0;

	GPIOA_CRH = 0x0;
	GPIOB_CRH = 0x0;

    //portA1 input (high Z) floating input
	GPIOA_CRL &= ~(0b11 <<4);
	GPIOA_CRL |=(0b01<<6);   //floating input

	//portB1 output push pull mode
	GPIOB_CRL |=(0b01<<4);	//speed 10 MHz
	GPIOB_CRL &= ~(0b11<<6);   //output


	//portA13 input (high Z) floating input
	GPIOA_CRH &= ~(0b11 << 20);
	GPIOA_CRH |=(0b01<<22);  //floating input

	//portB13 output push pull mode
	GPIOB_CRH |=(0b01<<20);  //speed 10 MHz
	GPIOA_CRH &= ~(0b11<<22);  //output


}



void delay(int x)
{
	unsigned int i,j;

	for (i=0 ; i<x ;i++)
	{
		for (j=0 ;j<255;j++);
	}
}
int main()
{

    clock_init();
    GPIO_init();



    while(1)
    {
    	//PORT A
    	if ( ((GPIOA_IDR & (1<<1)) >> 1) == 0) //single press
    	{
    		GPIOB_ODR ^= 1<<1;
    		while(((GPIOA_IDR & (1<<1)) >> 1) == 0);

    	}

    	//PORT B
    	if ( ((GPIOA_IDR & (1<<13)) >> 13) == 1) //multi pressing
    	{
    		GPIOB_ODR ^= 1<<13;
    	}

    	delay(1);
    }
}
