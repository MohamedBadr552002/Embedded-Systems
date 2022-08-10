/*
 * lifo.h
 *
 *  Created on: Aug 8, 2022
 *      Author: Mohamed
 */

#ifndef _H_LIFO
#define _H_LIFO

#include "stdio.h"
#include "stdlib.h"
//type definition
typedef struct {
	unsigned int length;
	unsigned int count;
	unsigned int *base;
	unsigned int *head;

}LIFO_BUF_t;


typedef enum{
	LIFO_no_error,
	LIFO_full,
	LIFO_empty,
	LIFO_Null
}BUFFER_status;


//APIs
BUFFER_status LIFO_Add_item (LIFO_BUF_t* lbuf,unsigned char item);
BUFFER_status LIFO_pop_item (LIFO_BUF_t* lbuf,unsigned char* item);
BUFFER_status LIFO_init     (LIFO_BUF_t* lbuf,unsigned int* buf,unsigned int length);


#endif
