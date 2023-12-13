/*
 * CortexMX_Porting.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Mohamed
 */

#ifndef INC_CORTEXMX_PORTING_H_
#define INC_CORTEXMX_PORTING_H_


#include "core_cm3.h"

extern int _estack ;
extern int _eheap;
#define MainStackSize 3072

#define OS_SET_PSP(add)			__asm volatile("mov r0,%0 \n\t msr PSP,r0": :"r"(add))
#define OS_GET_PSP(add)			__asm volatile("mrs r0,PSP \n\t mov %0,r0": "=r"(add))
#define OS_SWITCH_SP_to_PSP		__asm volatile("mrs r0,CONTROL \n\t mov r1,#0x02 \n\t orr r0,r0,r1 \n\t msr CONTROL,r0")
#define OS_SWITCH_SP_to_MSP		__asm volatile("mrs r0,CONTROL \n\t mov r1,#0x05 \n\t and r0,r0,r1 \n\t msr CONTROL,r0")
#define OS_Generate_Exception	__asm volatile("SVC #0x3")


#define OS_SWITCH_TO_PRIVILADGE	__asm("mrs r3,CONTROL \t\n" \
                  	  	  	  	  	  "lsr r3,r3,#0x1 \t\n" \
                  	  	  	  	  	  "lsl r3,r3,#0x1 \t\n" \
                  	  	  	  	  	  "msr CONTROL,r3");


#define OS_SWITCH_TO_UNPRIVILADGE              __asm("mrs r3,CONTROL \t\n" \
													 "orr r3,r3,#0x1 \t\n"\
                  	  	  	  	  	  	  	  	  	 "msr CONTROL,r3");


#endif /* INC_CORTEXMX_PORTING_H_ */
