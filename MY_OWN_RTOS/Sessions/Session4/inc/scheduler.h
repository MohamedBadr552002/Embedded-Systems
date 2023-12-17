/*
 * scheduler.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Mohamed
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "CortexMX_Porting.h"


typedef enum {
	no_error,
	Ready_Queue_init_error,
	Task_exceeded_StackSize
}OS_State_ID;


typedef struct{
	unsigned int stack_size;
	unsigned char priority;
	void(* p_task)(void); //pointer to function
	unsigned char Auto_start;
	unsigned int S_PSP;  		//Not entered by the user
	unsigned int E_PSP;			//Not entered by the user
	unsigned int *Current_PSP;	//Not entered by the user
	char task_name[30];
	enum{
		suspend,
		running,
		waiting,
		ready
	}Task_State;
	struct{
		enum{
			enable,
			Disable,
		}Blocking; //Not entered by the user
		unsigned int Ticks_count;
	}Timing_waiting;

}Task_ref;

// * =======================================================================================
// * =======================================================================================
//                              	APIs
// * =======================================================================================
// * =======================================================================================
OS_State_ID RTOS_INIT();
OS_State_ID RTOS_Create_Task(Task_ref* Task);
void RTOS_ActivateTask(Task_ref *Task);
void RTOS_TerminateTask(Task_ref *Task);
void RTOS_WaitingTask(unsigned int TICKS /*In ms*/,Task_ref *Task);
void RTOS_START();



#endif /* INC_SCHEDULER_H_ */
