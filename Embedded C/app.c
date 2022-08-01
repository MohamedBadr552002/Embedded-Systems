#include "uart.h"

unsigned char string_buffer[100]="Learn in depth:mohamed";
void main(void)
{
	Uart_Sent_String(string_buffer);
}