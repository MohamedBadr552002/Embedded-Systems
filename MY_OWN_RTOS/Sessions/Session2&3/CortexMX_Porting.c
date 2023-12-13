/*
 * CortexMX_Porting.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Mohamed
 */

#include "CortexMX_Porting.h"


uint8_t systicker ;

  void HardFault_Handler(void){
	  while(1);
  }
  void	MemManage_Handler(void){
	  while(1);
  }
  void	BusFault_Handler(void){
	  while(1);
  }
  void	UsageFault_Handler(void){
	  while(1);
  }

  __attribute ((naked)) void SVC_Handler()
  {
  	__asm("tst lr, #4 \t\n"
  		  "ITE EQ \t\n"
  		  "mrseq r0,MSP \t\n"
  		  "mrsne r0,PSP \t\n"
  		  "B OS_SVC");
  }


 void HardWare_INIT(){
	 	//Initialize Clock Tree(RCC -> Systick Timer & CPU) 8MHz
	 	//Init Hardware
	 	//RCC Default  values make Systick Timer Clock & CPU Clock = 8MHz
	 	// 1 count ->0.125us
	    // x count ->1 ms
	    // x = 8000 count



		//	decrease PenSV  interrupt priority to be  smaller than or equal  SySTICK Timer
	 	//to Switch context for previous task not SySTICK
		//SysTICK have a priority 14
		__NVIC_SetPriority(PendSV_IRQn, 15) ;



  }


 void OS_trigger_PendSV(){
 	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
 }

 void Start_Ticker()
 {
 	//	This clock tree should be defined in HW_init()
 	//	8 MHZ
 	//	1 count -> 0.125 us
 	//	X count -> 1 ms
 	//	X = 8000 Count

 	 SysTick_Config(8000);


 }

 void SysTick_Handler(void){

	 systicker ^=1;
	 //Update schedule
	 Decide_Next();
	 //Context and restore
	 OS_trigger_PendSV();

 }
