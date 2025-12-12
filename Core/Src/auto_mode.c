/*
 * fsm.c
 *
 *  Created on: Oct 2, 2025
 *      Author: Dell
 */

#include <auto_mode.h>
#include "config_mode.h"
#include "manual_mode.h"

uint8_t red_time = RED_TIME;
uint8_t grn_time = GRN_TIME;
uint8_t yel_time = YEL_TIME;

uint8_t ver_clock = 0;
uint8_t hor_clock = 0;

uint8_t traffic_light_status = INIT;

#define TICKS_PER_SECOND 20

// Static counters (in 10ms ticks)
static uint16_t state_counter = 0;
static uint16_t clock_counter = 0;

// Helper function to update counters - returns 1 if second elapsed
static uint8_t update_counters(void) {
	uint8_t second_elapsed = 0;
	
	if (clock_counter > 0) {
		clock_counter--;
	}
	if (state_counter > 0) {
		state_counter--;
	}
	
	// Check if 1 second has passed
	if (clock_counter == 0) {
		if (ver_clock > 0) ver_clock--;
		if (hor_clock > 0) hor_clock--;
		clock_counter = TICKS_PER_SECOND;
		second_elapsed = 1;
	}
	
	return second_elapsed;
}

// Helper function to display clocks on LCD
static void display_clocks(void) {
	lcd_goto_XY(1, 8);
	lcd_send_integer(ver_clock);
	lcd_goto_XY(0, 8);
	lcd_send_integer(hor_clock);
}

// Helper function to check button inputs and handle mode changes
static uint8_t check_buttons(void) {
	if (isButtonPressed(&button0)) {
		disable_all_tfl();
		traffic_light_status = CFG_RED;
		init_cfg_red();
		return 1;
	}
	if (isButtonPressed(&button1)) {
		traffic_light_status = MAN_GRN_RED;
		return 1;
	}
	return 0;
}

void init_auto_mode() {
	lcd_clear_display();

	lcd_goto_XY(0, 0);
	lcd_send_string("Road 1: ");
	lcd_goto_XY(1, 0);
	lcd_send_string("Road 2: ");

	traffic_light_status = AUTO_GRN_RED;
	ver_clock = grn_time;
	hor_clock = red_time;
	state_counter = grn_time * TICKS_PER_SECOND;
	clock_counter = TICKS_PER_SECOND;
}

// Getter function to read clock_counter
//uint16_t get_clock_counter(void) {
//	return clock_counter;
//}

void fsm_auto_traffic_light_run() {
	switch(traffic_light_status) {
		case INIT:
			init_auto_mode();
			break;
			
		case AUTO_GRN_RED:
			green_red();
			display_clocks();
			
			if (update_counters()) {
				lcd_clear_display();
			}
			
			// Transition to next state
			if (state_counter == 0) {
				traffic_light_status = AUTO_YEL_RED;
				ver_clock = yel_time;
				hor_clock = yel_time;
				state_counter = yel_time * TICKS_PER_SECOND;
				clock_counter = TICKS_PER_SECOND;
			}
			
			check_buttons();
			break;
			
		case AUTO_YEL_RED:
			yellow_red();
			display_clocks();

			if (update_counters()) {
				lcd_clear_display();
			}
			
			if (state_counter == 0) {
				traffic_light_status = AUTO_RED_GRN;
				ver_clock = red_time;
				hor_clock = grn_time;
				state_counter = grn_time * TICKS_PER_SECOND;
				clock_counter = TICKS_PER_SECOND;
			}

			check_buttons();
			break;
			
		case AUTO_RED_GRN:
			red_green();
			display_clocks();

			if (update_counters()) {
				lcd_clear_display();
			}
			
			if (state_counter == 0) {
				traffic_light_status = AUTO_RED_YEL;
				ver_clock = yel_time;
				hor_clock = yel_time;
				state_counter = yel_time * TICKS_PER_SECOND;
				clock_counter = TICKS_PER_SECOND;
			}

			check_buttons();
			break;
			
		case AUTO_RED_YEL:
			red_yellow();
			display_clocks();

			if (update_counters()) {
				lcd_clear_display();
			}
			
			if (state_counter == 0) {
				traffic_light_status = AUTO_GRN_RED;
				ver_clock = grn_time;
				hor_clock = red_time;
				state_counter = grn_time * TICKS_PER_SECOND;
				clock_counter = TICKS_PER_SECOND;
			}

			check_buttons();
			break;
			
		default:
			break;
	}
}

void disable_all_tfl() {

	HAL_GPIO_WritePin(TL0_0_GPIO_Port, TL0_0_Pin, 0);
	HAL_GPIO_WritePin(TL0_1_GPIO_Port, TL0_1_Pin, 0);

	HAL_GPIO_WritePin(TL1_0_GPIO_Port, TL1_0_Pin, 0);
	HAL_GPIO_WritePin(TL1_1_GPIO_Port, TL1_1_Pin, 0);
}

void green_red() {
	lcd_goto_XY(0, 0);
	lcd_send_string("Road 1: ");
	lcd_goto_XY(1, 0);
	lcd_send_string("Road 2: ");

	HAL_GPIO_WritePin(TL0_0_GPIO_Port, TL0_0_Pin, 1);
	HAL_GPIO_WritePin(TL0_1_GPIO_Port, TL0_1_Pin, 0);

	HAL_GPIO_WritePin(TL1_0_GPIO_Port, TL1_0_Pin, 1);
	HAL_GPIO_WritePin(TL1_1_GPIO_Port, TL1_1_Pin, 1);
}
void yellow_red() {
	lcd_goto_XY(0, 0);
	lcd_send_string("Road 1: ");
	lcd_goto_XY(1, 0);
	lcd_send_string("Road 2: ");

	HAL_GPIO_WritePin(TL0_0_GPIO_Port, TL0_0_Pin, 0);
	HAL_GPIO_WritePin(TL0_1_GPIO_Port, TL0_1_Pin, 1);

	HAL_GPIO_WritePin(TL1_0_GPIO_Port, TL1_0_Pin, 1);
	HAL_GPIO_WritePin(TL1_1_GPIO_Port, TL1_1_Pin, 1);
}
void red_green() {
	lcd_goto_XY(0, 0);
	lcd_send_string("Road 1: ");
	lcd_goto_XY(1, 0);
	lcd_send_string("Road 2: ");

	HAL_GPIO_WritePin(TL0_0_GPIO_Port, TL0_0_Pin, 1);
	HAL_GPIO_WritePin(TL0_1_GPIO_Port, TL0_1_Pin, 1);

	HAL_GPIO_WritePin(TL1_0_GPIO_Port, TL1_0_Pin, 1);
	HAL_GPIO_WritePin(TL1_1_GPIO_Port, TL1_1_Pin, 0);
}
void red_yellow() {
	lcd_goto_XY(0, 0);
	lcd_send_string("Road 1: ");
	lcd_goto_XY(1, 0);
	lcd_send_string("Road 2: ");

	// Vertical road
	HAL_GPIO_WritePin(TL0_0_GPIO_Port, TL0_0_Pin, 1);
	HAL_GPIO_WritePin(TL0_1_GPIO_Port, TL0_1_Pin, 1);

	HAL_GPIO_WritePin(TL1_0_GPIO_Port, TL1_0_Pin, 0);
	HAL_GPIO_WritePin(TL1_1_GPIO_Port, TL1_1_Pin, 1);
}

