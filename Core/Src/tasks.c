/*
 * tasks.c
 *
 *  Created on: Nov 16, 2025
 *      Author: Dell
 */

#include "tasks.h"
#include "auto_mode.h"  // Để lấy clock_counter


void task_toggle_status_led(void) {
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}

// Task: Run traffic light FSM (auto mode + config mode)
void task_traffic_light_fsm(void) {
	// Run appropriate FSM based on current state
	getKeyInput(&button0);
	getKeyInput(&button1);
	getKeyInput(&button2);
//	getKeyInput(&button3);
	if (traffic_light_status <= AUTO_RED_YEL) {
		fsm_auto_traffic_light_run();
	} else if (traffic_light_status >= CFG_RED && traffic_light_status <= CFG_GRN) {
		fsm_config_traffic_light_run();
	} else if (traffic_light_status >= MAN_GRN_RED && traffic_light_status <= MAN_RED_YEL) {
		fsm_manual_traffic_light_run();
	}
}

void task_button_scan(void) {
	getKeyInput(&button0);
	getKeyInput(&button1);
	getKeyInput(&button2);
//	getKeyInput(&button3);
}

void display_all_clock(void) {
//	uint16_t counter = get_clock_counter();
//
//	if (counter > 99) counter = 99;
//
//	led7_write_number(counter);
}

void task_2led7(void) {
	display_all_clock();
}
