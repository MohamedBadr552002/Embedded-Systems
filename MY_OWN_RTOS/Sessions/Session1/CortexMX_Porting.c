/*
 * CortexMX_Porting.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Mohamed
 */

#include "CortexMX_Porting.h"


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



  }
