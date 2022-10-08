#include <stdio.h>
#include <stdlib.h>

typedef volatile unsigned int vuint32_t ;
//RCC
#define RCC_BASE    0x40021000
#define RCC_APB2RSTR    *(vuint32_t*) ((RCC_BASE)+0x0C)

//GPIO
#define GPIOA_BASE    0x40010800
#define GPIOA_CRL   *(vuint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH   *(vuint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR   *(vuint32_t *)(GPIOA_BASE + 0x0C)

//EXTI
#define EXTI_BASE   0x40010400
#define EXTI_IMR   *(vuint32_t *)(EXTI_BASE + 0x00) // interrupt mask register
#define EXTI_PR    *(vuint32_t *)(EXTI_BASE + 0x14)  //pending register ( write >>1 to clear in handler)
#define EXTI_SWIER    *(vuint32_t *)(EXTI_BASE + 0x10)  // software interrupt event register (by default = 0 we donot chane it for now)
#define EXTI_RTSR  *(vuint32_t *)(EXTI_BASE + 0x08) // raising trigger selection register

//AFOI     Alternate function I/O and debug configuration
#define  AFIO_BASE    0x40010000
#define AFIO_EXTICR1  *(vuint32_t *)(AFIO_BASE + 0x00)  // external interrupt configuration register

#define NVIC_EXTERN0  *(vuint32_t *)(0xE000E100)

void clock_init()
{
    //enable clock GPIO
    RCC_APB2RSTR |= 1<<2;

    //altarnative function enable
    RCC_APB2RSTR |=1<<1;

}

void GPIO_init()
{
    //pin 13 portA
    GPIOA_CRH &= 0xFF0FFFFF;
    GPIOA_CRH |= 0x00200000;

    //pin A0 input floating
    GPIOA_CRL |=(1<<2);

}


int main()
{

    clock_init()
    GPIO_init()
    //EXTI x configuration to portA0
    AFIO_EXTICR1 |=(1<<0)
    //enable EXTI line 0 (mask 1)
    EXTI_IMR |= (1<<0);

    // enable raising trigger
    EXTI_RTSR |=(1<<0)

    //enable NVIC
    NVIC_EXTERN0 |=(1<<6);


    while(1);
}
void IQRhandler(void)
{
    //led toggle
    GPIOA_ODR ^=(1<<13);

    //clear Pending register
    EXTI_PR |=(1<<0)

}
