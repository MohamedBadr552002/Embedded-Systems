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


Task_ref task1,task2,task3,task4 ,task5,task6,task7,task8;
uint8_t task1LED,task2LED,task3LED, task4LED ,task5LED,task6LED,task7LED ,task8LED ;


void Task1(){
	static int count_1 =0;
	while(1){
		task1LED ^=1;

	}
}

void Task2(){
	static int count_2 =0;
	while(1){
		task2LED ^=1;


	}
}

void Task3(){
	static int count_3 =0;
	while(1){
		task3LED ^=1;


	}
}

void Task4(){
	static int count_4 =0;
	while(1){
		task4LED ^=1;


	}
}

void Task5(){
	static int count_1 =0;
	while(1){
		task5LED ^=1;

	}
}

void Task6(){
	static int count_2 =0;
	while(1){
		task6LED ^=1;


	}
}

void Task7(){
	static int count_3 =0;
	while(1){
		task7LED ^=1;


	}
}

void Task8(){
	static int count_4 =0;
	while(1){
		task8LED ^=1;


	}
}






int main()
{
	OS_State_ID rtos_state;
	HardWare_INIT();

	rtos_state = RTOS_INIT();

	if(rtos_state != no_error)
		while(1);





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


	task6.stack_size = 100;
	task6.priority =4;
	task6.p_task = Task6;
	strcpy(task6.task_name,"task6");

	task7.stack_size = 100;
	task7.priority =3;
	task7.p_task = Task7;
	strcpy(task7.task_name,"task7");

	task5.stack_size = 100;
	task5.priority =2;
	task5.p_task = Task5;
	strcpy(task5.task_name,"task5");

	task8.stack_size = 100;
	task8.priority =1;
	task8.p_task = Task8;
	strcpy(task8.task_name,"task8");



	rtos_state += RTOS_Create_Task(&task1);
	rtos_state += RTOS_Create_Task(&task2);
	rtos_state += RTOS_Create_Task(&task3);
	rtos_state += RTOS_Create_Task(&task4);
	rtos_state += RTOS_Create_Task(&task5);
	rtos_state += RTOS_Create_Task(&task6);
	rtos_state += RTOS_Create_Task(&task7);
	rtos_state += RTOS_Create_Task(&task8);



	RTOS_ActivateTask(&task1);
	RTOS_ActivateTask(&task2);
	RTOS_ActivateTask(&task3);
	RTOS_ActivateTask(&task4);
	RTOS_ActivateTask(&task5);
	RTOS_ActivateTask(&task6);
	RTOS_ActivateTask(&task7);
	RTOS_ActivateTask(&task8);



	RTOS_START();

    while(1)
    {


    }
}













