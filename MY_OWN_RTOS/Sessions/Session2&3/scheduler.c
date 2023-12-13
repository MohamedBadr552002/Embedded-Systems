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

typedef enum {
	SVC_Activatetask,
	SVC_terminatetask,
	SVC_TaskWaitingTime,
	SVC_AquireMutex,
	SVC_ReleaseMutex
}SVC_ID;


FIFO_Buf_t Ready_QUEUE ;
Task_ref* Ready_QUEUE_FIFO[100] ;

Task_ref rtos_idleTask ;


uint8_t idleLED;


// * =======================================================================================
// * =======================================================================================
//                               Private Interfacing with APIs
// * =======================================================================================
// * =======================================================================================
__attribute((naked)) void pendSV_Handler(){
		//====================================
		//Save the Context of the Current Task
		//====================================
		//Get the Current Task "Current PSP from CPU register" as CPU Push XPSR,.....,R0

		OS_GET_PSP(OS_Control.Current_task->Current_PSP);

		//using this Current_PSP (Pointer) tp store (R4 to R11)
		OS_Control.Current_task->Current_PSP-- ;
		__asm volatile("mov %0,r4 " : "=r" (*(OS_Control.Current_task->Current_PSP--))  );
		__asm volatile("mov %0,r5 " : "=r" (*(OS_Control.Current_task->Current_PSP--))  );
		__asm volatile("mov %0,r6 " : "=r" (*(OS_Control.Current_task->Current_PSP--))  );
		__asm volatile("mov %0,r7 " : "=r" (*(OS_Control.Current_task->Current_PSP--))  );
		__asm volatile("mov %0,r8 " : "=r" (*(OS_Control.Current_task->Current_PSP--))  );
		__asm volatile("mov %0,r9 " : "=r" (*(OS_Control.Current_task->Current_PSP--))  );
		__asm volatile("mov %0,r10 " : "=r" (*(OS_Control.Current_task->Current_PSP--))  );
		__asm volatile("mov %0,r11 " : "=r" (*(OS_Control.Current_task->Current_PSP--))  );

		//save the current Value of PSP
		//already saved in Current_PSP


		//====================================
		//Restore the Context of the Next Task
		//====================================

		__asm volatile("mov r11,%0 " : : "r" (*(OS_Control.Current_task->Current_PSP))  );
		OS_Control.Current_task->Current_PSP++ ;
		__asm volatile("mov r10,%0 " : : "r" (*(OS_Control.Current_task->Current_PSP))  );
		OS_Control.Current_task->Current_PSP++ ;
		__asm volatile("mov r9,%0 " : : "r" (*(OS_Control.Current_task->Current_PSP))  );
		OS_Control.Current_task->Current_PSP++ ;
		__asm volatile("mov r8,%0 " : : "r" (*(OS_Control.Current_task->Current_PSP))  );
		OS_Control.Current_task->Current_PSP++ ;
		__asm volatile("mov r7,%0 " : : "r" (*(OS_Control.Current_task->Current_PSP))  );
		OS_Control.Current_task->Current_PSP++ ;
		__asm volatile("mov r6,%0 " : : "r" (*(OS_Control.Current_task->Current_PSP))  );
		OS_Control.Current_task->Current_PSP++ ;
		__asm volatile("mov r5,%0 " : : "r" (*(OS_Control.Current_task->Current_PSP))  );
		OS_Control.Current_task->Current_PSP++ ;
		__asm volatile("mov r4,%0 " : : "r" (*(OS_Control.Current_task->Current_PSP))  );
		OS_Control.Current_task->Current_PSP++ ;

		//update PSP and exit
		OS_SET_PSP(OS_Control.Current_task->Current_PSP);
		__asm volatile("BX LR");

}


void Decide_Next(){
	/*
	It checks if the ready queue (Ready_QUEUE) is empty and the current task (OS_Control.CurrentTask) is not suspended.
			If so, the current task is set to the running state and added back to the ready queue using the FIFO_enqueue function to implement the round-robin scheduling algorithm.


	Otherwise, the next task is dequeued from the ready queue using the FIFO_dequeue function and set to the running state.
			If the current task has the same priority as the next task and is not suspended, it is added back to the ready queue and its state is set to ready.
			The selected next task is stored in OS_Control.NextTask.
	*/

	//if Ready Queue is empty && OS_Control->currentTask != suspend
	if(Ready_QUEUE.counter == 0 && OS_Control.Current_task->Task_State != suspend){
		OS_Control.Current_task->Task_State = running;
		FIFO_enqueue(&Ready_QUEUE, OS_Control.Current_task);
		OS_Control.Next_task = OS_Control.Current_task;
	}else{
		FIFO_dequeue(&Ready_QUEUE,&OS_Control.Next_task);
		OS_Control.Next_task->Task_State = running;
		//Update schaduler  as Round  Robin
		if((OS_Control.Current_task->priority == OS_Control.Next_task->priority) && (OS_Control.Current_task->Task_State != suspend)){
			FIFO_enqueue(&Ready_QUEUE, OS_Control.Current_task);
			OS_Control.Current_task->Task_State =ready;
		}
	}

}

void bubbleSort(){
		unsigned int i, j , n;
		Task_ref* temp ;
		n = OS_Control.No_Activated_tasks ;
		for (i = 0; i < n - 1; i++)

			// Last i elements are already in place
			for (j = 0; j < n - i - 1; j++){
				if (OS_Control.OS_Tasks[j]->priority > OS_Control.OS_Tasks[j + 1]->priority)
				{
					temp = OS_Control.OS_Tasks[j] ;
					OS_Control.OS_Tasks[j] = OS_Control.OS_Tasks[j + 1 ] ;
					OS_Control.OS_Tasks[j + 1] = temp ;
				}
			}
}

void rtos_update_schaduleTable(){
	Task_ref* temp =NULL ;
	Task_ref* Ptask ;
	Task_ref* PnextTask ;
	int i = 0 ;

	//1- bubble sort SchTable OS_Control-> OSTASKS[100] (priority high then low)
	bubbleSort();
	//2- free Ready Queue
	while(FIFO_dequeue(&Ready_QUEUE, &temp) != FIFO_EMPTY);
	//Update Ready Queue
	while(i< OS_Control.No_Activated_tasks){
		Ptask = OS_Control.OS_Tasks[i] ;
		PnextTask = OS_Control.OS_Tasks[i+1] ;
		if(Ptask->Task_State != suspend){
			//check if the current task is not suspended and the next one is suspended
			if(PnextTask->Task_State == suspend){
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->Task_State = ready;
				break;
			}

			if(Ptask->priority < PnextTask->priority){
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->Task_State = ready;
				break;
			}else if(Ptask->priority == PnextTask->priority){
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->Task_State = ready;
			}
		}
		i++;
	}
}


void OS_SVC(int * Stack_frame)
{
	//r0,10,r2,r3,r12,LR,PC,xPCS
	unsigned char SVC_Number;
	SVC_Number = *((unsigned char*)(((unsigned char*) Stack_frame[6])-2));

	switch(SVC_Number)
	{
	case SVC_Activatetask:  //Activate Task
	case SVC_terminatetask://Terminate Task
		//Update sch Queue
		rtos_update_schaduleTable();
		//OS is on Running State
		if(OS_Control.OSmodeID == OS_running){
			if(strcmp(OS_Control.Current_task->task_name,"idleTask") != 0){
				//Decide what is next
				Decide_Next();
				//trigger PendSV (Switch and Restore)
				OS_trigger_PendSV();
			}
		}

		break;
	case SVC_TaskWaitingTime: //

		break;

	}


}





void rtos_SVC_Set( SVC_ID SVC_ID)
{

	switch(SVC_ID)
	{
	case SVC_Activatetask:  //activate Task
		__asm("svc #0x00");
		break;
	case SVC_terminatetask: //termenate Task
		__asm("svc #0x01");
		break;
	case SVC_TaskWaitingTime: //
		__asm("svc #0x02");
		break;

	}

}

void IDEL_TASK()
{
	idleLED ^=1;
	while(1){

		__asm("NOP");
	}
}


void Rtos_Create_MainStack(){

	OS_Control._S_MSP = &_estack;
	OS_Control._E_MSP = (OS_Control._S_MSP - MainStackSize);
	//Align 8 byte between MSP and PSP
	OS_Control.PSP_Task_Locator = (OS_Control._E_MSP - 8);



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

	Task->Current_PSP = (uint32_t *)Task->S_PSP;

	*(-- Task->Current_PSP) = 0x01000000;  //XPSR

	*(-- Task->Current_PSP) = (uint32_t)Task->p_task; //PC

	*(--Task->Current_PSP) = 0xFFFFFFFD; //LR

	for(int i=0;i<13;i++){
		*(--Task->Current_PSP)= 0;
	}


}



// * =======================================================================================
// * =======================================================================================
//                               APIs Implementation
// * =======================================================================================
// * =======================================================================================
OS_State_ID RTOS_INIT(){

	OS_State_ID state = no_error;

	//Update OS Mode(OS Suspend)
	OS_Control.OSmodeID = OS_suspend;
	//Specify the Main Stack for OS
	Rtos_Create_MainStack();
	//Create OS Ready Queue
	if(FIFO_init(&Ready_QUEUE, Ready_QUEUE_FIFO, 100) != FIFO_NO_ERROR)
	{
		state += Ready_Queue_init_error ;
	}
	//Configure IDLE TASK
	strcpy(rtos_idleTask.task_name,"idleTask");
	rtos_idleTask.priority = 255;
	rtos_idleTask.stack_size =300;
	rtos_idleTask.p_task = IDEL_TASK;


	state += RTOS_Create_Task(&rtos_idleTask);

	return state ;

}

OS_State_ID RTOS_Create_Task(Task_ref* Task)
{
	OS_State_ID error = no_error ;

	//Create Its OWN PSP stack
	//Check task stack size exceeded the PSP stack
	Task->S_PSP = OS_Control.PSP_Task_Locator;
	Task->E_PSP = Task->S_PSP - Task->stack_size ;

	if(Task->E_PSP < (uint32_t)(&(_eheap))){
		return Task_exceeded_StackSize ;
	}

	//Align 8 Bytes between tasks Stacks
	OS_Control.PSP_Task_Locator = Task->E_PSP -8 ;

	//Initialize PSP Task Stack
	RTOS_Create_Stack(Task);

	//Update Schedule Table
	OS_Control.OS_Tasks[OS_Control.No_Activated_tasks++] = Task;

	//Task State Update
	Task->Task_State = suspend;

	return error;

}

void RTOS_ActivateTask(Task_ref *Task){
	Task->Task_State = waiting;
	rtos_SVC_Set(SVC_Activatetask);

}

void RTOS_TerminateTask(Task_ref *Task){
	Task->Task_State = suspend;


}

void RTOS_START(){
	OS_Control.OSmodeID = OS_running;
	//set the default current task to idle task
	OS_Control.Current_task = &rtos_idleTask;
	//Activate Idle task
	RTOS_ActivateTask(&rtos_idleTask);
	//start ticker
	Start_Ticker(); //1ms
	//set PSP
	OS_SET_PSP(OS_Control.Current_task->S_PSP);

	//Switch tread mode change SP from MSP to PSP
	OS_SWITCH_SP_to_PSP;
	OS_SWITCH_TO_UNPRIVILADGE;
	rtos_idleTask.p_task();
}



