/*
 * tasks.h
 *
 *  Created on: Nov 16, 2025
 *      Author: Dell
 */

#ifndef INC_TASKS_H_
#define INC_TASKS_H_

#include <led_7_seg.h>
#include "main.h"
#include "global.h"
#include "auto_mode.h"
#include "config_mode.h"
#include "manual_mode.h"
#include "button.h"

// Task functions for scheduler
void task_timer_run(void);
void task_toggle_status_led(void);
void task_traffic_light_fsm(void);
void task_button_scan(void);
void task_display_7seg(void);
void task_2led7(void);

#endif /* INC_TASKS_H_ */
