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
	Task_exceeded_StackSize,
	MaxNumerOfTasksForMutex
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

typedef struct{
	uint8_t *pPayload;
	uint32_t PayloadSize;
	Task_ref *Current_user;
	Task_ref *Next_user;
	char name[30];
}Mutex_ref;

// * =======================================================================================
// * =======================================================================================
//                              	APIs
// * =======================================================================================
// * =======================================================================================


/**================================================================
* @Fn				- RTOS_INIT
* @brief		    - Initialize the OS to be ready to work By Creating Main Stack and put the OS in Suspend State
* @param [in] 		- none
* @retval		    - Return the State of the OS According to initialization operation
* Note				- This Function not used for Start the OS just for Initialization
*==================================================================*/
OS_State_ID RTOS_INIT();

/**================================================================
* @Fn				- RTOS_START
* @brief		    - Start the Scheduling  Operation
* @param [in] 		- none
* @retval		    - none
* Note				- Ticker Time is 1 ms
*==================================================================*/
void RTOS_START();

/**================================================================
* @Fn				- RTOS_Create_Task
* @brief		    - Create Real time Task By Preparing Task Stack
* @param [in] 		- Struct for Task properties
* @retval		    - Return the State of the OS
* Note				- Task was put in Suspend State until Activation Command
*==================================================================*/
OS_State_ID RTOS_Create_Task(Task_ref* Task);

/**================================================================
* @Fn				- RTOS_ActivateTask
* @brief		    - Activate Task and put it in Ready or Working State
* @param [in] 		- Struct for Task properties
* @retval		    - none
* Note				- Task was put in Waiting State until OS Schedule Decision
*==================================================================*/
void RTOS_ActivateTask(Task_ref *Task);

/**================================================================
* @Fn				- RTOS_TerminateTask
* @brief		    - Put task in Suspend State and stop working
* @param [in] 		- Struct for Task properties
* @retval		    - none
*==================================================================*/
void RTOS_TerminateTask(Task_ref *Task);

/**================================================================
* @Fn				- RTOS_WaitingTask
* @brief		    - Put task in Waiting State For Specific Time
* @param [in] 		- Waiting time in ms
* @param [in] 		- Struct for Task properties
* @retval		    - none
*==================================================================*/
void RTOS_WaitingTask(unsigned int TICKS /*In ms*/,Task_ref *Task);

/**================================================================
* @Fn				- RTOS_AquireMutex
* @brief		    - Task try to Take this Mutex
* @param [in] 		- Struct for Mutex
* @param [in] 		- Struct for Task
* @retval		    - Return the State of the OS
* @Note				- Just Two task can Take this Mutex
*==================================================================*/
OS_State_ID RTOS_AquireMutex(Mutex_ref * Mutex , Task_ref *next_user);

/**================================================================
* @Fn				- RTOS_ReleaseMutex
* @brief		    - Release this Mutex from this Task
* @param [in] 		- Struct for Mutex
* @retval		    - none
*==================================================================*/
void RTOS_ReleaseMutex(Mutex_ref *Mutex);



#endif /* INC_SCHEDULER_H_ */
