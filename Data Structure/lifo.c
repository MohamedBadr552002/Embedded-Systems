/*
 * lifo.c
 *
 *  Created on: Aug 8, 2022
 *      Author: Mohamed
 */
#include "lifo.h"

BUFFER_status LIFO_Add_item (LIFO_BUF_t* lbuf,unsigned char item)
{
	//check lifo is vaild
	if(!lbuf->base || !lbuf->head)
		return LIFO_Null;

	//check lifo is full
	if(lbuf->count == lbuf->length)
		return LIFO_full;

	//add value
	*(lbuf->head)=item;
	lbuf->head++;
	lbuf->count++;

	return LIFO_no_error;

}
BUFFER_status LIFO_pop_item (LIFO_BUF_t* lbuf,unsigned char* item)
{
	   //check lifo is vaild
		if(!lbuf->base || !lbuf->head)
			return LIFO_Null;
		//check lifo is empty
		if(lbuf->count == 0)
			return LIFO_empty;

		lbuf->head--;
		*item =*(lbuf->head);
		lbuf->count--;
		return LIFO_no_error;



}
BUFFER_status LIFO_init     (LIFO_BUF_t* lbuf,unsigned int* buf,unsigned int length)
{
	if(buf == NULL)
		return LIFO_Null;

	lbuf->base=buf;
	lbuf->head=buf;
	lbuf->length=length;
	lbuf->count=0;
	return LIFO_no_error;
}
