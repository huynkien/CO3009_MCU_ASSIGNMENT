/*
 * manual_mode.h
 *
 *  Created on: Nov 3, 2025
 *      Author: Dell
 */

#ifndef INC_MANUAL_MODE_H_
#define INC_MANUAL_MODE_H_

#include "main.h"
#include "auto_mode.h"
#include "global.h"
#include "button.h"


void fsm_manual_traffic_light_run();

void man_green_red();
void man_yellow_red();
void man_red_green();
void man_red_yellow();



#endif /* INC_MANUAL_MODE_H_ */
