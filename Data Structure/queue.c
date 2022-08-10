/*
 * queue.c
 *
 *  Created on: Aug 8, 2022
 *      Author: Mohamed
 */

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"


//select element type (uint8_t /uint16_t / uint32_t)
#define element_type uint8_t

#define width 5
element_type buffer1[width];

typedef struct {
	    unsigned int length;
		unsigned int count;
		element_type *base;
		element_type *head;
		element_type *tail;
}FIFO_buf_t;

typedef enum{
	    FIFO_no_error,
		FIFO_full,
		FIFO_empty,
		FIFO_Null
}Buffer_status;

//APIs

Buffer_status FIFO_init (FIFO_buf_t* fifo ,element_type* buff ,uint32_t length);
Buffer_status FIFO_enqueue (FIFO_buf_t* fifo ,element_type temp );
Buffer_status FIFO_dequeue (FIFO_buf_t* fifo ,element_type* temp );
void print (FIFO_buf_t* fifo  );


void main()
{
	unsigned char i , temp=0;
	FIFO_buf_t UART_fifo;
	if(FIFO_init(&UART_fifo,buffer1,width)== FIFO_no_error)
		printf("FIFO init is DONE \n");
	//FIFO Enqueue
	for(i=0;i< 7;i++)
	{
		printf("FIFO Enqueue : %x\n ",i);
		if(FIFO_enqueue(&UART_fifo,i) == FIFO_no_error)
			printf("FIFO Enqueue %X  DONE\n",i);
		else
			printf("FIFO Enqueue %X  FAILED \n",i);

	}
	//FIFO print
	print(&UART_fifo);

	//FIFO dequeue
	if(FIFO_dequeue(&UART_fifo,&temp) == FIFO_no_error)
		printf("FIFO Dequeue %X  DONE\n",temp);
	if(FIFO_dequeue(&UART_fifo,&temp) == FIFO_no_error)
		printf("FIFO Dequeue %X  DONE\n",temp);
	//FIFO print
	print(&UART_fifo);


}


Buffer_status FIFO_init (FIFO_buf_t* fifo ,element_type* buff ,uint32_t length)
{
	if(buff == NULL)
		return FIFO_Null;

	fifo->base=buff;
	fifo->tail=buff;
	fifo->head=buff;
	fifo->count=0;
	fifo->length=length;

	return FIFO_no_error;
}

Buffer_status FIFO_enqueue (FIFO_buf_t* fifo ,element_type temp )
{
	//buff exist
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_Null;
	// is full ?
	if(fifo->length != fifo->count)
	{
		*(fifo->head)= temp;

		fifo->count++;
		//circler fifo
		if(fifo->head ==fifo->base + (fifo->length * sizeof(element_type)))
			fifo->head == fifo->base;
		else
			fifo->head++;

		return FIFO_no_error;
	}
	else
	{
		printf("FIFO enqueue failed \n");
		return FIFO_full;
	}
}

Buffer_status FIFO_dequeue (FIFO_buf_t* fifo ,element_type* temp )
{
	//buff exist
		if(!fifo->base || !fifo->head || !fifo->tail)
			return FIFO_Null;
	//is buff empty ?
		if(fifo->count==0)
		{
			printf("FIFO is empty\n");
			return FIFO_empty;
		}
		*temp= *(fifo->tail);
		fifo->count--;

		//circler fifo
		if(fifo->tail ==fifo->tail + (fifo->length * sizeof(element_type)))
			fifo->tail == fifo->base;
		else
			fifo->tail++;

		return FIFO_no_error;

}
void print (FIFO_buf_t* fifo  )
{
	element_type* temp;
	        if(fifo->count==0)
			{
				printf("FIFO is empty\n");
				return FIFO_empty;
			}

	        temp=fifo->tail;
	        printf("=====FIFO print======\n");
	        for(int i=0;i<fifo->count;i++)
	        {
	        	printf(" %x \n",*temp);
	        	temp++;

	        }
	        printf("============\n");

}



