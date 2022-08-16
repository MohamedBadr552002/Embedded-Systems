/*
 * collision avoidance.c
 *
 *  Created on: Aug 16, 2022
 *      Author: Mohamed
 */

#include "collision avoidance.h"
#include "state.h"

//variables

int CA_speed=0;
int CA_distance=0;
int threshold=50;


//state pointer to function
void (*CA_pointer)();




void US_get_distance(int d)
{
	CA_distance=d;
	(CA_distance <= threshold) ? (CA_pointer=ST_CA_waiting):(CA_pointer=ST_CA_driving);
	printf("US-------distance=%d-------->CA \n",CA_distance);
}

void ST_CA_waiting()
{
	//state name
	CA_state_id= waiting;
	printf("CA_waiting state: distance= %d   speed=%d \n",CA_distance,CA_speed);
	//state action
	CA_speed=0;
	DC_motor(CA_speed);
	//US get distance



}

void ST_CA_driving()
{
	    //state name
	    CA_state_id=driving;
	    printf("CA_driving state: distance= %d   speed=%d",CA_distance,CA_speed);
		//state action
	    CA_speed=30;
		DC_motor(CA_speed);
		//US get distance


}

