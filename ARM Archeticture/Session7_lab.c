#include "core_cm3.h"

void OS_SVC(int * Stack_frame)
{
	//r0,10,r2,r3,r12,LR,PC,xPCS
	unsigned char SVC_Number;
	unsigned int val1,val2;

	SVC_Number = *((unsigned char*)(((unsigned char*) Stack_frame[6])-2));
	val1 = Stack_frame[0];
	val2 =Stack_frame[1];



	switch(SVC_Number)
	{
	case 0:  //OS_ADD
		Stack_frame[0] = val1 + val2;
		break;
	case 1: //OS SUB
		Stack_frame[0] = val1 - val2;
		break;
	case 2: //OS_MUL
		Stack_frame[0] = val1 * val2;
		break;

	}


}



__attribute ((naked)) void SVC_Handler()
{
	__asm("tst lr, #4 \t\n"
		  "ITE EQ \t\n"
		  "mrseq r0,MSP \t\n"
		  "mrsne r0,PSP \t\n"
		  "B OS_SVC");
}


int OS_SVC_Set(int a ,int b, int SVC_ID)
{
	int result;
	switch(SVC_ID)
	{
	case 0:  //OS_ADD
		__asm("svc  #0x00");
		break;
	case 1: //OS SUB
		__asm("svc  #0x01");
		break;
	case 2: //OS_MUL
		__asm("svc  #0x02");
		break;

	}
	__asm("mov %0,r0":"=r"(result));
	return result;
}




int main()
{


	OS_SVC_Set(9,4,0);
	OS_SVC_Set(9,4,1);
	OS_SVC_Set(1,4,2);

    while(1)
    {


    }
}
