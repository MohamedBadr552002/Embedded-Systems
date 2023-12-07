/*
 * scheduler.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Mohamed
 */

#include "scheduler.h"
#include "RTOS_FIFO.h"



struct{
	Task_ref* OS_Tasks[100]; // sch table
	unsigned int _S_MSP;
	unsigned int _E_MSP;
	unsigned int PSP_Task_Locator;
	unsigned int No_Activated_tasks;
	Task_ref* Current_task;
	Task_ref* Next_task;
	enum{
		OS_suspend,
		OS_running
	}OSmodeID;

}OS_Control;


FIFO_Buf_t Ready_QUEUE ;
Task_ref* Ready_QUEUE_FIFO[100] ;

Task_ref rtos_idleTask ;


void OS_SVC(int * Stack_frame)
{
	//r0,10,r2,r3,r12,LR,PC,xPCS
	unsigned char SVC_Number;


	SVC_Number = *((unsigned char*)(((unsigned char*) Stack_frame[6])-2));

	switch(SVC_Number)
	{
	case 0:  //Activate Task

		break;
	case 1://Terminate Task

		break;
	case 2: //

		break;

	}


}


void pendSV_Handler(){


}


void OS_SVC_Set( int SVC_ID)
{

	switch(SVC_ID)
	{
	case 0:  //activate Task
		__asm("svc  #0x00");
		break;
	case 1: //termenate Task
		__asm("svc  #0x01");
		break;
	case 2: //
		__asm("svc  #0x02");
		break;

	}

}


void Rtos_Create_MainStack(){

	OS_Control._S_MSP = &_estack;
	OS_Control._E_MSP = OS_Control._S_MSP - MainStackSize;
	//Align 8 byte between MSP and PSP
	OS_Control.PSP_Task_Locator = OS_Control._E_MSP - 8;



}


void RTOS_IDEL_TASK()
{
	while(1){

		__asm("NOP");
	}
}

RTOS_State_ID RTOS_INIT(){

	RTOS_State_ID state = no_error;

	//Update OS Mode(OS Suspend)
	OS_Control.OSmodeID = OS_suspend;
	//Specify the Main Stack for OS
	Rtos_Create_MainStack();
	//Create OS Ready Queue
	if(FIFO_init(&Ready_QUEUE, Ready_QUEUE_FIFO, 100))
	{
		state += Ready_Queue_init_error ;
	}
	//Configure IDLE TASK
	strcpy(rtos_idleTask.task_name,"idleTask");
	rtos_idleTask.priority = 255;
	rtos_idleTask.stack_size =300;
	rtos_idleTask.p_task = RTOS_IDEL_TASK;


	state += RTOS_Create_Task(RTOS_IDEL_TASK);

	return state ;

}


void RTOS_Create_Stack(Task_ref* Task)
{
	/*Task Frame
	 * ======
	 * XPSR
	 * PC (Next Task Instruction which should be Run)
	 * LR (return register which is saved in CPU while TASk1 running before TaskSwitching)
	 * r12
	 * r4
	 * r3
	 * r2
	 * r1
	 * r0
	 *====
	 *r5, r6 , r7 ,r8 ,r9, r10,r11 (Saved/Restore)Manual
	 */

	Task->Current_PSP = Task->S_PSP;

	*(-- Task->Current_PSP) = 0x01000000;  //XPSR

	*(-- Task->Current_PSP) = (uint32_t)Task->p_task; //PC

	*(--Task->Current_PSP) = 0xFFFFFFFD; //LR

	for(int i=0;i<13;i++){
		*(--Task->Current_PSP)= 0;
	}


}

RTOS_State_ID RTOS_Create_Task(Task_ref* Task)
{
	RTOS_State_ID error = no_error ;

	//Create Its OWN PSP stack
	//Check task stack size exceeded the PSP stack
	Task->S_PSP = OS_Control.PSP_Task_Locator;
	Task->E_PSP = Task->S_PSP - Task->stack_size ;

	if(Task->E_PSP < (uint32_t)(&(_eheap))){
		return Task_exceeded_StackSize ;
	}

	//Align 8 Bytes between tasks Stacks
	OS_Control.PSP_Task_Locator = OS_Control._E_MSP -8 ;

	//Initialize PSP Task Stack
	RTOS_Create_Stack(Task);

	//Task State Update
	Task->Task_State = suspend;

	return error;

}



