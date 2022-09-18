typedef volatile unsigned int vuint32_t ;
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
// register address
#define GPIOA_BASE 0x40010800
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)


//clock register
#define RCC_BASE 0x4002100
#define RCC_CFGR (vuint32_t *)(RCC_BASE+0x04)
#define RCC_RCC_APB2ENR (vuint32_t *)(RCC_BASE+0x18)
#define RCC_CR (vuint32_t *)(RCC_BASE+0x0)

int main(void)
{   //
    RCC_RCC_APB2ENR |= 1<<2;

    //init clock

   // PLL enable
   RCC_CR |= 1<<24;

   //PLL entry clock source selected HSI
   RCC_CFGR |= 0<<16;

   //PLL multiplication factor (input clock x8)
   RCC_CFGR |= 0b0110<<18;

   //System clock switch (PLL selected as system clock)
   RCC_CFGR |= 0b10<<0;

   //system clock 32MHz


   // APB low-speed prescaler (APB1) divided by 2
   RCC_CFGR |= 0b100<<8;
   // APB high-speed prescaler (APB2) divided by 4
   RCC_CFGR |= 0b101<<11;


    //Init GPIOA
    GPIOA_CRH &= 0xFF0FFFFF;
    GPIOA_CRH |= 0x00200000;
    while(1)
    {
    GPIOA_ODR |= 1<<13 ;
    for (int i = 0; i < 5000; i++); // arbitrary delay
    GPIOA_ODR &= ~(1<<13) ;
    for (int i = 0; i < 5000; i++); // arbitrary delay
    }
}
