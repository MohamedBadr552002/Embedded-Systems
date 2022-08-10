/*
 * main.c
 *
 *  Created on: Aug 8, 2022
 *      Author: Mohamed
 */

#include "lifo.h"
#include "stdio.h"
#include "stdlib.h"

unsigned int buffer1[20];





void main()
{
	int temp=0;
	LIFO_BUF_t uart_lifo , I2C_lifo ;

	LIFO_init(&uart_lifo,buffer1,5);

	unsigned int* buffer2 =(unsigned int*) malloc(5* sizeof(unsigned int) );

	//LIFO_init(I2C_lifo,buffer2,5);


	for(int i=0 ;i<5;i++)
	{
		if(LIFO_Add_item(&uart_lifo,i)==LIFO_no_error)
			printf ("UART_add :%d \n",i);
	}

	for(int i=0 ;i<5;i++)
	{
		if(LIFO_pop_item(&uart_lifo, &temp)==LIFO_no_error)
			printf ("UART_add :%d \n",temp);
	}

}
