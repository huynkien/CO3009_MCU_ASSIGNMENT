/*
 * fsm.c
 *
 *  Created on: Oct 2, 2025
 *      Author: Dell
 */

#include <auto_mode.h>
#include "config_mode.h"
#include "manual_mode.h"
#include "software_timer.h"

uint8_t red_time = RED_TIME;
uint8_t grn_time = GRN_TIME;
uint8_t yel_time = YEL_TIME;

uint8_t ver_clock = 0;
uint8_t hor_clock = 0;

uint8_t traffic_light_status = INIT;

static uint8_t last_ver_clock = 255;
static uint8_t last_hor_clock = 255;

// Only update LCD when values change
static void display_clocks(void) {
	if (ver_clock != last_ver_clock) {
		lcd_goto_XY(1, 8);
		lcd_send_integer(ver_clock);
		lcd_send_string("  ");  // clear old digits
		last_ver_clock = ver_clock;
	}
	if (hor_clock != last_hor_clock) {
		lcd_goto_XY(0, 8);
		lcd_send_integer(hor_clock);
		lcd_send_string("  ");  // clear old digits
		last_hor_clock = hor_clock;
	}
}

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
	
	// reset LCD tracking
	last_ver_clock = 255;
	last_hor_clock = 255;
	
	green_red();
	
	setTimer(TIMER_STATE, grn_time * TICKS_PER_SECOND);
	setTimer(TIMER_CLOCK, TICKS_PER_SECOND);
}

void fsm_auto_traffic_light_run() {
	switch(traffic_light_status) {
		case INIT:
			init_auto_mode();
			break;
			
		case AUTO_GRN_RED:
			display_clocks();
			
			if (isTimerExpired(TIMER_CLOCK)) {
				if (ver_clock > 0) ver_clock--;
				if (hor_clock > 0) hor_clock--;
				setTimer(TIMER_CLOCK, TICKS_PER_SECOND);
			}
			
			if (isTimerExpired(TIMER_STATE)) {
				traffic_light_status = AUTO_YEL_RED;
				ver_clock = yel_time;
				hor_clock = yel_time;
				last_ver_clock = 255; 
				last_hor_clock = 255;
				yellow_red();
				setTimer(TIMER_STATE, yel_time * TICKS_PER_SECOND);
			}
			
			check_buttons();
			break;
			
		case AUTO_YEL_RED:
			display_clocks();

			if (isTimerExpired(TIMER_CLOCK)) {
				if (ver_clock > 0) ver_clock--;
				if (hor_clock > 0) hor_clock--;
				setTimer(TIMER_CLOCK, TICKS_PER_SECOND);
			}
			
			if (isTimerExpired(TIMER_STATE)) {
				traffic_light_status = AUTO_RED_GRN;
				ver_clock = red_time;
				hor_clock = grn_time;
				last_ver_clock = 255;
				last_hor_clock = 255;
				red_green();
				setTimer(TIMER_STATE, grn_time * TICKS_PER_SECOND);
			}

			check_buttons();
			break;
			
		case AUTO_RED_GRN:
			display_clocks();

			if (isTimerExpired(TIMER_CLOCK)) {
				if (ver_clock > 0) ver_clock--;
				if (hor_clock > 0) hor_clock--;
				setTimer(TIMER_CLOCK, TICKS_PER_SECOND);
			}
			
			if (isTimerExpired(TIMER_STATE)) {
				traffic_light_status = AUTO_RED_YEL;
				ver_clock = yel_time;
				hor_clock = yel_time;
				last_ver_clock = 255;
				last_hor_clock = 255;
				red_yellow();
				setTimer(TIMER_STATE, yel_time * TICKS_PER_SECOND);
			}

			check_buttons();
			break;
			
		case AUTO_RED_YEL:
			display_clocks();

			if (isTimerExpired(TIMER_CLOCK)) {
				if (ver_clock > 0) ver_clock--;
				if (hor_clock > 0) hor_clock--;
				setTimer(TIMER_CLOCK, TICKS_PER_SECOND);
			}
			
			if (isTimerExpired(TIMER_STATE)) {
				traffic_light_status = AUTO_GRN_RED;
				ver_clock = grn_time;
				hor_clock = red_time;
				last_ver_clock = 255;
				last_hor_clock = 255;
				green_red();
				setTimer(TIMER_STATE, grn_time * TICKS_PER_SECOND);
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
	HAL_GPIO_WritePin(TL0_0_GPIO_Port, TL0_0_Pin, 1);
	HAL_GPIO_WritePin(TL0_1_GPIO_Port, TL0_1_Pin, 0);

	HAL_GPIO_WritePin(TL1_0_GPIO_Port, TL1_0_Pin, 1);
	HAL_GPIO_WritePin(TL1_1_GPIO_Port, TL1_1_Pin, 1);
}
void yellow_red() {
	HAL_GPIO_WritePin(TL0_0_GPIO_Port, TL0_0_Pin, 0);
	HAL_GPIO_WritePin(TL0_1_GPIO_Port, TL0_1_Pin, 1);

	HAL_GPIO_WritePin(TL1_0_GPIO_Port, TL1_0_Pin, 1);
	HAL_GPIO_WritePin(TL1_1_GPIO_Port, TL1_1_Pin, 1);
}
void red_green() {
	HAL_GPIO_WritePin(TL0_0_GPIO_Port, TL0_0_Pin, 1);
	HAL_GPIO_WritePin(TL0_1_GPIO_Port, TL0_1_Pin, 1);

	HAL_GPIO_WritePin(TL1_0_GPIO_Port, TL1_0_Pin, 1);
	HAL_GPIO_WritePin(TL1_1_GPIO_Port, TL1_1_Pin, 0);
}
void red_yellow() {
	// Vertical road
	HAL_GPIO_WritePin(TL0_0_GPIO_Port, TL0_0_Pin, 1);
	HAL_GPIO_WritePin(TL0_1_GPIO_Port, TL0_1_Pin, 1);

	HAL_GPIO_WritePin(TL1_0_GPIO_Port, TL1_0_Pin, 0);
	HAL_GPIO_WritePin(TL1_1_GPIO_Port, TL1_1_Pin, 1);
}

