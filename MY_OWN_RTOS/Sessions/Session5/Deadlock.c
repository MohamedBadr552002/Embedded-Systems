/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mohamed Badr
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
#include "core_cm3.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif



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
#include "scheduler.h"


Task_ref task1,task2,task3,task4;
uint8_t task1LED,task2LED,task3LED, task4LED;

Mutex_ref Mutex1;
Mutex_ref Mutex2;

uint8_t array[3] = {1,2,3};
uint8_t array2[3] = {1,2,3};

void Task1(){
	static int count_1 =0;
	while(1){
		task1LED ^=1;
		count_1 ++;
		if(count_1 == 100){
		   RTOS_AquireMutex(&Mutex1, &task1);
		   RTOS_ActivateTask(&task4);
		   RTOS_AquireMutex(&Mutex2, &task1);
		}
		if(count_1 ==200){
			count_1 =0;
			RTOS_ReleaseMutex(&Mutex1);
		}

	}
}

void Task2(){
	static int count_2 =0;
	while(1){
		task2LED ^=1;
		count_2 ++;
		if(count_2 == 100){

		   RTOS_ActivateTask(&task3);
		}
		if(count_2 ==200){
			count_2 =0;
			RTOS_TerminateTask(&task2);
		}

	}


}

void Task3(){
	static int count_3 =0;
	while(1){
		task3LED ^=1;
		count_3 ++;
		if(count_3 == 100){

		   RTOS_ActivateTask(&task4);
		}
		if(count_3 ==200){
			count_3 =0;
			RTOS_TerminateTask(&task3);
		}

	}

}

void Task4(){
	static int count_4 =0;
	while(1){
		task4LED ^=1;
		count_4 ++;
		if(count_4 == 3){

			RTOS_AquireMutex(&Mutex2, &task4);
		   RTOS_AquireMutex(&Mutex1, &task4);
		}
		if(count_4 ==200){
			count_4 =0;
			RTOS_ReleaseMutex(&Mutex1);
			RTOS_TerminateTask(&task4);
		}

	}


}






int main()
{
	OS_State_ID rtos_state;
	HardWare_INIT();

	rtos_state = RTOS_INIT();

	if(rtos_state != no_error)
		while(1);


	Mutex1.pPayload = array;
	Mutex1.PayloadSize =3;
	strcpy(Mutex1.name,"Mutex1");
	Mutex1.priority_inheriting.state = priority_inheritance_disable;


	Mutex2.pPayload = array2;
	Mutex2.PayloadSize =3;
	strcpy(Mutex2.name,"Mutex2");
	Mutex2.priority_inheriting.state = priority_inheritance_disable;



	task1.stack_size = 100;
	task1.priority =7;
	task1.p_task = Task1;
	strcpy(task1.task_name,"task1");

	task2.stack_size = 100;
	task2.priority =6;
	task2.p_task = Task2;
	strcpy(task2.task_name,"task2");

	task3.stack_size = 100;
	task3.priority =5;
	task3.p_task = Task3;
	strcpy(task3.task_name,"task3");

	task4.stack_size = 100;
	task4.priority =4;
	task4.p_task = Task4;
	strcpy(task4.task_name,"task4");





	rtos_state += RTOS_Create_Task(&task1);
	rtos_state += RTOS_Create_Task(&task2);
	rtos_state += RTOS_Create_Task(&task3);
	rtos_state += RTOS_Create_Task(&task4);




	RTOS_ActivateTask(&task1);



	RTOS_START();

    while(1)
    {


    }
}













