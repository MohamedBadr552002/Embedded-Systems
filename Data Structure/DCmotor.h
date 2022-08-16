/*
 * DC_motor.h
 *
 *  Created on: Aug 16, 2022
 *      Author: Mohamed
 */

#include "stdio.h"
#include "stdlib.h"


#ifndef DCMOTOR_H_
#define DCMOTOR_H_


 enum{
	 idle,
	 busy
 } DC_state_id;

void ST_DC_idle();
void ST_DC_busy();

void DC_init();

extern void (*DC_pointer)();

#endif /* DCMOTOR_H_ */
