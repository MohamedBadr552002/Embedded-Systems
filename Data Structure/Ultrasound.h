/*
 * collision avoidance.h
 *
 *  Created on: Aug 16, 2022
 *      Author: Mohamed
 */

#include "stdio.h"
#include "stdlib.h"


#ifndef ULTRASOUND_H_
#define ULTRASOUND_H_


 enum{
	 US_busy
 } US_state_id;


 void ST_US_busy();


void US_init();

extern void (*US_pointer)();

#endif /* ULTRASOUND_H_ */
