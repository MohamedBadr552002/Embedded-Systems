/*
 * collision avoidance.h
 *
 *  Created on: Aug 16, 2022
 *      Author: Mohamed
 */

#include "stdio.h"
#include "stdlib.h"


#ifndef COLLISION_AVOIDANCE_H_
#define COLLISION_AVOIDANCE_H_


 enum{
	 waiting,
	 driving
 } CA_state_id;


void ST_CA_waiting();
void ST_CA_driving();



extern void (*CA_pointer)();

#endif /* COLLISION_AVOIDANCE_H_ */
