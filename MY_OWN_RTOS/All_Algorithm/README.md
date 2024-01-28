# This Real-Time Operating System Was designed based on:
* Online Static Priority
* Pre-emtive 
* Round-robin Schedualing Time-shared Algorithm

#### Which mean that scheduler Makes Decision about task execution and Priorities During Run time also the higher Priority task interrupt the lower one .
#### About the time shared Algorithm between the same Priority tasks the Round-Robin Algorithm take the responsibilty.

# Algorithm Over view 
### Note : this OS Was implemented and Tested on Stm32f103c6 based on Corex-M3 processor .
### Systick Generate Handler Interrupt each 1 millisecond.
![RTOS](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/d30bc7d1-549b-4fc3-8f4d-de26f46036a5)




# Task States 
##### this OS Could hep me to set the comming State for each Task to schedule between them
* suspend : In this state, the task has been suspended by another task or by the system. it's not participating in scheduling process and can not be selected for 
            execution.
* running : In this state, the task is currently executing excuting by the processor.
* waiting : In this state, the task is waiting for an event to occur or a resource to become available. It's not participating in the scheduling process and can 
            not be selected for execution until the event or resource become avalible.
* ready   : In this state, the task is ready to  run but is waiting for the processor to become avalible. `It's placed in a ready queue and is waiting for the 
           scheduler to select`.

#### In case of Suspended for all Tasks the OS Execute the idle task which led the CPU to be in Sleep mode and waiting for event to start up again to reduce the consumed power.
![Screenshot 2023-12-16 233938](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/392e8739-d4e8-4e18-9121-3bc00c5ea7de)

# Schedule Table Updating
### This Os support Bubble and Merge Sorting Algorithms for updating the scheduale of tasks
### But after Analysis and Measurments of Performance found that Bubble sort is more efficient.
#### Here is Test operation for 8 Tasks not including idle task tasted with ordered Priority meanning the highest created first and Reversed Priority Meanning the lowest Created First Noted that any test case was updating just once before the Stating of OS .

## Bubble Sorting 
![BubbleorderedPriority](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/8cd2b8f9-6084-420e-aa27-1143999a3266)

![bubbleReversePeriority](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/faaa33ab-5dee-4ce4-beb1-dbe6760ef427)

## Merge Sorting 
![MegeOrederedPriority](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/b9e550d5-ee3f-4577-9ab1-27ba5dc240b2)

![mergeReversePriority](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/1ade0609-f618-4fa9-8b0a-8eb7fb66f5fb)



# Tasks Synchronization
#### This OS Support Mutex across making one task to acquire a Specific Mutex also one Task can be in waiting state for Relesing of the mutex.
![Screenshot 2024-01-24 181135](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/adce5bc3-d6b6-4e5c-a06e-af36f76b89b5)
####   `But this led to Priority Inversion Problem !!`
##  Priority Inversion 
the problem happen when low priority task holds a resource required by high priority task leading to delay the execution of the highest one.
the Algorithim Uses __`Priority Inheritance Solution `__

## Priority Inheritance Solution
#### It's a Resource access Control Protocol that temporarily raise the priority of a Low-priority Task holding a shared resource to the high-priority Task that needs the resource.
![image](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/6d4e066a-9130-4326-b034-4364fc44907e)

## DeadLock Problem
##### deadlock occur when two or more tasks are waiting for each other to release resources that they hold.
![Screenshot 2024-01-26 232638](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/c20f0be7-03f1-40cb-9fbb-c24b792d1511)
### But the Operating System provide a solution for this problem by stopping any task from acquiring more than one Mutex .
![image](https://github.com/MohamedBadr552002/Embedded-Systems/assets/108628976/f3aacc73-760c-46f3-9e87-6610c26ec9f7)


# APIs
```c
/**================================================================
* @Fn				- RTOS_INIT
* @brief		    - Initialize the OS to be ready to work By Creating Main Stack and put the OS in Suspend State
* @param [in] 		- none
* @retval		    - Return the State of the OS According to initialization operation
* Note				- This Function not used for Start the OS just for Initialization
*==================================================================*/
OS_State_ID RTOS_INIT();
```
```c
/**================================================================
* @Fn				- RTOS_START
* @brief		    - Start the Scheduling  Operation
* @param [in] 		- none
* @retval		    - none
* Note				- Ticker Time is 1 ms
*==================================================================*/
void RTOS_START();
```

```c
/**================================================================
* @Fn				- RTOS_Create_Task
* @brief		    - Create Real time Task By Preparing Task Stack
* @param [in] 		- Struct for Task properties
* @retval		    - Return the State of the OS
* Note				- Task was put in Suspend State until Activation Command
*==================================================================*/
OS_State_ID RTOS_Create_Task(Task_ref* Task);
```

```c
/**================================================================
* @Fn				- RTOS_ActivateTask
* @brief		    - Activate Task and put it in Ready or Working State
* @param [in] 		- Struct for Task properties
* @retval		    - none
* Note				- Task was put in Waiting State until OS Schedule Decision
*==================================================================*/
void RTOS_ActivateTask(Task_ref *Task);
```

```c
/**================================================================
* @Fn				- RTOS_TerminateTask
* @brief		    - Put task in Suspend State and stop working
* @param [in] 		- Struct for Task properties
* @retval		    - none
*==================================================================*/
void RTOS_TerminateTask(Task_ref *Task);
```

```c
/**================================================================
* @Fn				- RTOS_WaitingTask
* @brief		    - Put task in Waiting State For Specific Time
* @param [in] 		- Waiting time in ms
* @param [in] 		- Struct for Task properties
* @retval		    - none
*==================================================================*/
void RTOS_WaitingTask(unsigned int TICKS /*In ms*/,Task_ref *Task);
```
```c
/**================================================================
* @Fn				- RTOS_AquireMutex
* @brief		    - Task try to Take this Mutex
* @param [in] 		- Struct for Mutex
* @param [in] 		- Struct for Task
* @retval		    - Return the State of the OS
* @Note				- Just Two task can Take this Mutex
*==================================================================*/
OS_State_ID RTOS_AquireMutex(Mutex_ref * Mutex , Task_ref *next_user);
```

```c
/**================================================================
* @Fn				- RTOS_ReleaseMutex
* @brief		    - Release this Mutex from this Task
* @param [in] 		- Struct for Mutex
* @retval		    - none
*==================================================================*/
void RTOS_ReleaseMutex(Mutex_ref *Mutex);
```
