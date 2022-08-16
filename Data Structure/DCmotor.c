/*
 * collision avoidance.c
 *
 *  Created on: Aug 16, 2022
 *      Author: Mohamed
 */

#include "DCmotor.h"
#include "state.h"
//variables

int DC_speed=0;



//state pointer to function
void (*DC_pointer)();



void DC_init()
{
   printf("DC init \n");
}

void DC_motor(int s)
{
	DC_speed=s;
	DC_pointer = ST_DC_busy;
	printf("CA-------speed=%d-------->DC \n",DC_speed);
}

void ST_DC_idle()
{
	//state name
	DC_state_id=idle;


	printf("DC_idle state:  speed=%d\n",DC_speed);

}

void ST_DC_busy()
{
	    //state name
	    DC_state_id=busy;
	    DC_pointer = ST_DC_idle;
		printf("DC_busy state:speed=%d",DC_speed);
}

