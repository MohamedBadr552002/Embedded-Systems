
#include <stdint.h>

extern int main(void);


void Rest_Handler (void);

void Defualt_Handler()
{
	Rest_Handler();
}

void NMI_Handler(void)         __attribute__ ((weak, alies ("Defualt_Handler")));;
void H_fault_Handler(void)     __attribute__ ((weak, alies ("Defualt_Handler")));;
void MM_Fault_Handler(void)    __attribute__ ((weak, alies ("Defualt_Handler")));;
void Bus_Fault(void)           __attribute__ ((weak, alies ("Defualt_Handler")));;
void Usage_Fault_Handler(void) __attribute__ ((weak, alies ("Defualt_Handler")));;


static unsigned long stack_top[265];


void (* const g_p_fn_vector[]() __attribute__(section(".vectors")))=
{
	(void (*)()) ((unsigned long)stack_top + sizeof(stack_top)),
	 &Rest_Handler,
     &NMI_Handler,
     &H_fault_Handler,
     &MM_Fault_Handler,
     &Bus_Fault,
     &Usage_Fault_Handler
};




extern unsigned int _S_DATA ;
extern unsigned int _E_DATA ;
extern unsigned int _E_text ;
extern unsigned int _S_bss ;
extern unsigned int _E_bss ;



void Rest_Handler(void)
{
	//copy data from ROM to RAM
	unsigned int DATA_size= (unsigned char*)&_E_DATA -(unsigned char*)&_S_DATA;
	unsigned char* p_scr= (unsigned char*)&_E_text;
	unsigned char* p_dst= (unsigned char*)&_S_DATA;
	for(int i=0;i<DATA_size;i++)
	{
		*((unsigned char*)p_dst++) = *((unsigned char*)p_src++);
	}
	//init the .bss with zero
	unsigned int bss_size= (unsigned char*)&_E_bss -(unsigned char*)&_S_bss;
	p_dst= (unsigned char*)&_S_bss;
     	for(int i=0;i<DATA_size;i++)
		{
			*((unsigned char*)p_dst++) = unsigned char 0;
		}
	
   main();	
}