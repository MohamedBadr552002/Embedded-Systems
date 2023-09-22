


#include "stm32f103c6.h"
#include "STM32F103C6_DRIVER_GPIO.h"
#include "keybad.h"
#include "LCD.h"
#include "7_segments.h"
#include "I2C_slave_EEPROM.h"
#include "Servo_Motor.h"
#include "STM32F103C6_DRIVER_EXTI.h"
#include "STM32F103C6_DRIVER_RCC.h"
#include "STM32F103C6_DRIVER_USART.h"
#include "STM32F103C6_DRIVER_SPI.h"
#include "STM32F103C6_DRIVER_I2C.h"
#include "STM32F103C6_DRIVER_TIMER.h"




#define OS_SET_PSP(add)			__asm volatile("mov r0,%0 \n\t msr PSP,r0": :"r"(add))
#define OS_SWITCH_SP_to_PSP		__asm volatile("mrs r0,CONTROL \n\t mov r1,#0x02 \n\t orr r0,r0,r1 \n\t msr CONTROL,r0")
#define OS_SWITCH_SP_to_MSP		__asm volatile("mrs r0,CONTROL \n\t mov r1,#0x05 \n\t and r0,r0,r1 \n\t msr CONTROL,r0")
#define OS_Generate_Exception	__asm volatile("SVC #0x3")

#define TaskA_stack_size 100
#define TaskB_stack_size 100

extern int _estack ;
//Main Stack
uint8_t _S_MSP = &_estack;
uint8_t _E_MSP;

//Task A stack
uint8_t _S_PSP_TA;
uint8_t _E_PSP_TA;

//Task A stack
uint8_t _S_PSP_TB;
uint8_t _E_PSP_TB;

uint8_t TASKA_flag,TASKB_flag,IRQ_flag=0;

enum CPU_AccessLevel{
    Privilaged,
    unPrivilaged
};




void Change_CPU_AccessLevel(enum CPU_AccessLevel level)
{
    switch(level)
    {
        case Privilaged:
            __asm("mov r3,CONTROL \t\n"
                  "lsr r3,r3,#0x1 \t\n"
                  "lsl r3,r3,#0x1 \t\n"
                  "msr CONTROL,r3");
            break;
        case unPrivilaged:
             __asm("mov r3,CONTROL \t\n"
                  "orr r3,r3,#0x1 \t\n"
                  "msr CONTROL,r3");
            break;
    }

}
void CLOCK_INIT()
{
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN() ;

}



void EXTI5PB5_OPEN_EXIT_GATE()
{
	if(IRQ_flag == 0)
	{
		TASKA_flag =1;
		IRQ_flag =1;
	}
	else if(IRQ_flag == 1)
	{
		TASKB_flag =1;
		IRQ_flag =0;
	}
}

int TaskA(int a , int b ,int c)
{
    //Task1 Operations
	return a+b+c;

}

int TaskB(int a , int b ,int c)
{
    //Task2 Operations
	return a*b*c;
}

void SVC_Handler()
{
	Change_CPU_AccessLevel(Privilaged);
}


void OS_Main()
{
	//Main stack
	_E_MSP =(_S_MSP - 512);

	//taskA stack
	_S_PSP_TA = (_E_MSP -8);
	_E_PSP_TA = (_S_PSP_TA - TaskA_stack_size);

	//taskB stack
	_S_PSP_TB = (_E_PSP_TA -8);
	_E_PSP_TB = (_S_PSP_TB - TaskB_stack_size);

	while(1)
	{
	__asm("NOP");

	if(TASKA_flag == 1)
	{
		//Set PSP Register = _S_PSP_TA
		OS_SET_PSP(_S_PSP_TA);
		//SP -> PSP
		OS_SWITCH_SP_to_PSP;
		//switch from Privilag to unPrivilag
		Change_CPU_AccessLevel(unPrivilaged);

		//Calling the Task
		TASKA_flag = TaskA(1,2,3);

		//switch from unPrivilag to Privilag
		OS_Generate_Exception;
		// SP -> MSP
	}
	else if(TASKB_flag == 1)
	{
		//Set PSP Register = _S_PSP_TA
		OS_SET_PSP(_S_PSP_TB);
		//SP -> PSP
		OS_SWITCH_SP_to_PSP;
		//switch from Privilag to unPrivilag
		Change_CPU_AccessLevel(unPrivilaged);

		//Calling the Task
		TASKB_flag =TaskB(1,2,3);

		//switch from unPrivilag to Privilag
		OS_Generate_Exception;
		// SP -> MSP
	}
	}
}


int main()
{
    CLOCK_INIT();


   	//PIR2 A1
	EXTI_Pinconfig_t PIR2 ;
	PIR2.EXTI_PIN = EXTI5PB5;
	PIR2.Trigger_Case = EXTI_TRIGGER_RAISING ;
	PIR2.P_IRQ_CallBack = EXTI5PB5_OPEN_EXIT_GATE ;
	PIR2.IRQ_EN = EXTI_IRQ_ENABLE;
	MCAL_EXTI_INIT(&PIR2);

	OS_Main();

    while(1)
    {


    }
}

