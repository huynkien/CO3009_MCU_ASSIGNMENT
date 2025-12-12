/*
 * config_mode.h
 *
 *  Created on: Oct 30, 2025
 *      Author: Dell
 */

#ifndef INC_CONFIG_MODE_H_
#define INC_CONFIG_MODE_H_

#include "main.h"
#include "global.h"
#include "button.h"
#include "auto_mode.h"

/* Main FSM function */
void fsm_config_traffic_light_run();

/* Init functions - called when entering each config state */
void init_cfg_red();
void init_cfg_yel();
void init_cfg_grn();

/* State run functions (private to FSM, but exposed for flexibility) */
void cfg_red();
void cfg_yel();
void cfg_grn();

/* LED control helpers */
void turn_off_on_both();
void turn_red_on_both();
void turn_yel_on_both();
void turn_grn_on_both();

#endif /* INC_CONFIG_MODE_H_ */
