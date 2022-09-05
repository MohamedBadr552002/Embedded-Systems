/*
 * pressure_sensor.h
 *
 *  Created on: Sep 3, 2022
 *      Author: Mohamed
 */

#ifndef PRESSURE_SENSOR_H_
#define PRESSURE_SENSOR_H_


#include "driver.h"
#include "state.h"

//sensor state

enum {
	P_busy
}PS_state_id;

//init sensor



void SP_PS_busy();

//state pointer to call functions
extern void (*PS_pointer)();

#endif /* PRESSURE_SENSOR_H_ */



