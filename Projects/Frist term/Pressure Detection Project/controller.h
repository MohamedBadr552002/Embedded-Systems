/*
 * controller.h
 *
 *  Created on: Sep 3, 2022
 *      Author: Mohamed
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "state.h"
#include "pressure_sensor.h"
#include "buzzer.h"
#include "driver.h"

enum{
	buzzer_off,
	buzzer_on
}con_state_id;



//state pointer to function

extern void (*P_controller)();

//functions
void ST_BUZZZER_on();
void ST_BUZZZER_off();


#endif /* CONTROLLER_H_ */
