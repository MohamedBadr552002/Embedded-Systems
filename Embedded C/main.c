
typedef volatile unsigned int vuint32_t;

#include <stdint.h>

#define RCC_BASE   0x40021000
#define GPIOA_BASE 0x40010800

#define RCC_APB2ENR  *(volatile uint32_t * )(RCC_BASE + 0x18)
#define GPIOA_CRH    *(volatile uint32_t * )(GPIOA_BASE + 0x04)
#define GPIOA_ODR    *(volatile uint32_t * )(GPIOA_BASE + 0x0c)

typedef union {
	vuint32_t all_fields ;
	struct {
		vuint32_t reversed :13;
		vuint32_t pin_13 :1;
	       }pin;
}R_ODR_t;

volatile R_ODR_t* R_ODR = (volatile R_ODR_t*)(GPIOA_BASE + 0x0c);

int main(void)
{
	RCC_APB2ENR |=1<<2;
	GPIOA_CRH   &=0xFF0FFFFF;
	GPIOA_CRH   |=0x00200000;
	while(1)
	{
	//	GPIOA_ODR |=1<<13; //set bit nu 13
		R_ODR->pin.pin_13 = 1;
		for(int i=0;i<=20000;i++);
	//	GPIOA_ODR &=~(1<<13); //clear bit nu 13
		R_ODR->pin.pin_13= 0 ;
		for(int i=0;i<=20000;i++);
		
			
	}
	
	return 0;
}
