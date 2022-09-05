
#include"stdint.h"
extern int main();
void Reset_Handler();
void Default_Handler()
{
	Reset_Handler();
}
void NMI_Handler() __attribute__((weak,alias("Default_Handler")));
void H_Fault_Handler()__attribute__((weak,alias("Default_Handler")));
void MM_Fault_Handler()__attribute__((weak,alias("Default_Handler")));
void Bus_Fault_Handler()__attribute__((weak,alias("Default_Handler")));
void Usage_Fault_Handler()__attribute__((weak,alias("Default_Handler")));

extern unsigned int _stack_top;

uint32_t vectors[] __attribute__((section(".vectors"))) = {
	(uint32_t) &_stack_top,
	(uint32_t) &Reset_Handler,
	(uint32_t) &NMI_Handler,
	(uint32_t) &H_Fault_Handler,
	(uint32_t) &MM_Fault_Handler,
	(uint32_t) &Bus_Fault_Handler,
	(uint32_t) &Usage_Fault_Handler
};


extern unsigned int _S_data;
extern unsigned int _E_data;
extern unsigned int _S_bss;
extern unsigned int _E_bss;
extern unsigned int _E_text;
int i;


void Reset_Handler()
{
	unsigned int DATA_SIZE = (unsigned char*)&_E_data - (unsigned char*)&_S_data;
	unsigned char* P_src = (unsigned char*)&_E_text;
	unsigned char* P_dst = (unsigned char*)&_S_data;
	for( i=0;i<DATA_SIZE;i++)
	{
		*((unsigned char*)P_dst++)=*((unsigned char*)P_src);
	}
	unsigned int bss_SIZE = (unsigned char*)&_E_bss - (unsigned char*)&_S_bss;
	P_dst=(unsigned char*)&_S_bss;
	for( i=0;i<DATA_SIZE;i++)
	{
		*((unsigned char*)P_dst++)=0;
	}
	main();
}