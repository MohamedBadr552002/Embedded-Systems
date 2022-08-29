#include "uart.h"

#define UART0DR *((volatile unsigned int*)((unsigned int *)0x101f1000))

void Uart_Sent_String(unsigned char *p_tx_string)
{
   while(*p_tx_string !='\0')
   {
	   UART0DR=(unsigned int)(*p_tx_string);
	   *p_tx_string++;
   }
}
