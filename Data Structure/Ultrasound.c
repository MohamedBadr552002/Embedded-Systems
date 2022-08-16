/*
 * collision avoidance.c
 *
 *  Created on: Aug 16, 2022
 *      Author: Mohamed
 */

#include "Ultrasound.h"
#include "state.h"
//variables


int US_distance=0;



//state pointer to function
void (*US_pointer)();

int get_distance_random(int l,int r,int count);

void US_init()
{
   printf("US init \n");
}

void ST_US_busy()
{
	//state name
	US_state_id=US_busy;
	//state action
	US_distance= get_distance_random(45,55,1);


	printf("CA_waiting state: distance= %d \n",US_distance);
	US_get_distance(US_distance);
	US_pointer=ST_US_busy;
}


int get_distance_random(int l,int r,int count)
{
	int random_num;
	for(int i=0;i< count ;i++)
	{

		random_num= (rand() %(r-l+1)) +1;
		return random_num;
	}
}
