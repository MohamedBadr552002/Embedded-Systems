/*
 * main.c
 *
 *  Created on: Aug 16, 2022
 *      Author: Mohamed
 */


#include "stdio.h"
#include "stdlib.h"
#include "collision avoidance.h"
#include "Ultrasound.h"
#include "DCmotor.h"
#include "state.h"


void setup()
{
	//init block
	DC_init();
	US_init();
	//set state pointer for each block
	CA_pointer =   ST_CA_waiting;
	DC_pointer =   ST_DC_idle;
	US_pointer =   ST_US_busy;
}


void main()
{
	volatile int i;
    setup();

   while(1)
   {
	   //call each state
	   US_pointer();
	   CA_pointer();
	   DC_pointer();

	   for(i=0;i<1000;i++);

   }
}
