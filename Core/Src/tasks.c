/*
 * tasks.c
 *
 *  Created on: Nov 16, 2025
 *      Author: Dell
 */

#include "tasks.h"
#include "auto_mode.h"
#include "software_timer.h"

void task_timer_run(void) {
	timerRun();
}

void task_toggle_status_led(void) {
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}

void task_traffic_light_fsm(void) {
	//get button signal
	getKeyInput(&button0);
	getKeyInput(&button1);
	getKeyInput(&button2);
	///FSMs
	if (traffic_light_status <= AUTO_RED_YEL) {
		fsm_auto_traffic_light_run();
	} else if (traffic_light_status >= CFG_RED && traffic_light_status <= CFG_GRN) {
		fsm_config_traffic_light_run();
	} else if (traffic_light_status >= MAN_GRN_RED && traffic_light_status <= MAN_RED_YEL) {
		fsm_manual_traffic_light_run();
	}
}

