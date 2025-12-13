/*
 * config_mode.c
 *
 *  Created on: Oct 30, 2025
 *      Author: Dell
 */

#include "config_mode.h"
#include "software_timer.h"

/*
 Green light:  [3, 90]
 Yellow light: [3, 9]
 Red light:    [6, 99]
 red_time = green_time + yellow_time
 */

#define GRN_MIN  1
#define GRN_MAX  99
#define YEL_MIN  1
#define YEL_MAX  99
#define RED_MIN  1
#define RED_MAX  99

static uint8_t red_temp_time = 0;
static uint8_t yel_temp_time = 0;
static uint8_t grn_temp_time = 0;

static uint8_t tl_status_all_led = 0;

static void display_config_lcd(char* color_name, uint8_t time_value) {
	lcd_clear_display();
	lcd_goto_XY(0, 0);
	lcd_send_string("MODE: CONFIG");
	lcd_goto_XY(1, 0);
	lcd_send_string(color_name);
	lcd_send_string(": ");
	lcd_send_integer(time_value);
	lcd_send_string("   ");
}

static uint8_t fix(uint8_t value, uint8_t min, uint8_t max) {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

void turn_off_on_both() {
	HAL_GPIO_WritePin(TL0_0_GPIO_Port, TL0_0_Pin, 0);
	HAL_GPIO_WritePin(TL0_1_GPIO_Port, TL0_1_Pin, 0);

	HAL_GPIO_WritePin(TL1_0_GPIO_Port, TL1_0_Pin, 0);
	HAL_GPIO_WritePin(TL1_1_GPIO_Port, TL1_1_Pin, 0);
}

void turn_red_on_both() {
	HAL_GPIO_WritePin(TL0_0_GPIO_Port, TL0_0_Pin, 1);
	HAL_GPIO_WritePin(TL0_1_GPIO_Port, TL0_1_Pin, 1);

	HAL_GPIO_WritePin(TL1_0_GPIO_Port, TL1_0_Pin, 1);
	HAL_GPIO_WritePin(TL1_1_GPIO_Port, TL1_1_Pin, 1);
}

void turn_yel_on_both() {
	HAL_GPIO_WritePin(TL0_0_GPIO_Port, TL0_0_Pin, 0);
	HAL_GPIO_WritePin(TL0_1_GPIO_Port, TL0_1_Pin, 1);

	HAL_GPIO_WritePin(TL1_0_GPIO_Port, TL1_0_Pin, 0);
	HAL_GPIO_WritePin(TL1_1_GPIO_Port, TL1_1_Pin, 1);
}

void turn_grn_on_both() {
	HAL_GPIO_WritePin(TL0_0_GPIO_Port, TL0_0_Pin, 1);
	HAL_GPIO_WritePin(TL0_1_GPIO_Port, TL0_1_Pin, 0);

	HAL_GPIO_WritePin(TL1_0_GPIO_Port, TL1_0_Pin, 1);
	HAL_GPIO_WritePin(TL1_1_GPIO_Port, TL1_1_Pin, 0);
}

static void confirm_red_time() {
	red_temp_time = fix(red_temp_time, RED_MIN, RED_MAX);
	int8_t calc_grn = red_temp_time - yel_time;
	
	if (calc_grn < GRN_MIN) calc_grn = GRN_MIN;
	if (calc_grn > GRN_MAX) calc_grn = GRN_MAX;
	
	grn_time = calc_grn;
	red_time = grn_time + yel_time;
	red_time = fix(red_time, RED_MIN, RED_MAX);
}

static void confirm_yel_time() {
	yel_temp_time = fix(yel_temp_time, YEL_MIN, YEL_MAX);
	
	uint8_t calc_grn = red_time - yel_temp_time;
	
	if (calc_grn < GRN_MIN) calc_grn = GRN_MIN;
	if (calc_grn > GRN_MAX) calc_grn = GRN_MAX;
	
	grn_time = calc_grn;
	red_time = grn_time + yel_temp_time;
	red_time = fix(red_time, RED_MIN, RED_MAX);
	yel_time = yel_temp_time;
}

static void confirm_grn_time() {
	grn_temp_time = fix(grn_temp_time, GRN_MIN, GRN_MAX);
	uint8_t calc_red = grn_temp_time + yel_time;
	
	if (calc_red > RED_MAX) {
		red_time = RED_MAX;
		grn_time = red_time - yel_time;
		grn_time = fix(grn_time, GRN_MIN, GRN_MAX);
	} else if (calc_red < RED_MIN) {
		red_time = RED_MIN;
		grn_time = red_time - yel_time;
		grn_time = fix(grn_time, GRN_MIN, GRN_MAX);
	} else {
		grn_time = grn_temp_time;
		red_time = calc_red;
	}
}

void init_cfg_red() {
	red_temp_time = red_time;
	
	turn_red_on_both();
	setTimer(TIMER_BLINK, CONFIG_BLINK_TICKS);
	tl_status_all_led = 1;
	
	display_config_lcd("t_RED", red_temp_time);
}

void cfg_red() {
	if (isTimerExpired(TIMER_BLINK)) {
		if (tl_status_all_led == 0) {
			turn_red_on_both();
			tl_status_all_led = 1;
		} else {
			turn_off_on_both();
			tl_status_all_led = 0;
		}
		setTimer(TIMER_BLINK, CONFIG_BLINK_TICKS);  // Reset blink timer
	}
}

void init_cfg_yel() {
	yel_temp_time = yel_time;
	
	turn_yel_on_both();
	setTimer(TIMER_BLINK, CONFIG_BLINK_TICKS);  // Set blink timer
	tl_status_all_led = 1;
	
	// Display on LCD
	display_config_lcd("t_YEL", yel_temp_time);
}

void cfg_yel() {
	// Check blink timer
	if (isTimerExpired(TIMER_BLINK)) {
		if (tl_status_all_led == 0) {
			turn_yel_on_both();
			tl_status_all_led = 1;
		} else {
			turn_off_on_both();
			tl_status_all_led = 0;
		}
		setTimer(TIMER_BLINK, CONFIG_BLINK_TICKS);
	}
}

void init_cfg_grn() {
	grn_temp_time = grn_time;
	
	turn_grn_on_both();
	setTimer(TIMER_BLINK, CONFIG_BLINK_TICKS);
	tl_status_all_led = 1;
	
	// Display on LCD
	display_config_lcd("t_GRN", grn_temp_time);
}

void cfg_grn() {
	// Check blink timer
	if (isTimerExpired(TIMER_BLINK)) {
		if (tl_status_all_led == 0) {
			turn_grn_on_both();
			tl_status_all_led = 1;
		} else {
			turn_off_on_both();
			tl_status_all_led = 0;
		}
		setTimer(TIMER_BLINK, CONFIG_BLINK_TICKS);
	}
}

void fsm_config_traffic_light_run() {
	switch (traffic_light_status) {
		case CFG_RED:
			cfg_red();
			
			if (isButtonPressed(&button0)) {
				traffic_light_status = CFG_YEL;
				init_cfg_yel();
			}
			
			if (isButtonPressed(&button1)) {
				red_temp_time++;
				uint8_t min_red = yel_time + GRN_MIN;
				if (red_temp_time > RED_MAX) {
					red_temp_time = min_red;
				}
				if (red_temp_time < min_red) {
					red_temp_time = min_red;
				}
				lcd_goto_XY(1, 7);
				lcd_send_integer(red_temp_time);
				lcd_send_string("  ");
			}

			if (isButtonPressed(&button2)) {
				confirm_red_time();
				init_cfg_red();
			}
			break;
			
		case CFG_YEL:
			cfg_yel();
			
			if (isButtonPressed(&button0)) {
				traffic_light_status = CFG_GRN;
				init_cfg_grn();
			}
			
			if (isButtonPressed(&button1)) {
				yel_temp_time++;
				if (yel_temp_time > YEL_MAX) {
					yel_temp_time = YEL_MIN;
				}
				if (yel_temp_time < YEL_MIN) {
					yel_temp_time = YEL_MIN;
				}
				lcd_goto_XY(1, 7);
				lcd_send_integer(yel_temp_time);
				lcd_send_string("  ");
			}

			if (isButtonPressed(&button2)) {
				confirm_yel_time();
				init_cfg_yel();
			}
			break;
			
		case CFG_GRN:
			cfg_grn();
			
			if (isButtonPressed(&button0)) {
				init_auto_mode();
			}
			
			if (isButtonPressed(&button1)) {
				grn_temp_time++;
				if (grn_temp_time > GRN_MAX) {
					grn_temp_time = GRN_MIN;
				}
				if (grn_temp_time < GRN_MIN) {
					grn_temp_time = GRN_MIN;
				}
				lcd_goto_XY(1, 7);
				lcd_send_integer(grn_temp_time);
				lcd_send_string("  ");
			}

			if (isButtonPressed(&button2)) {
				confirm_grn_time();
				init_cfg_grn();
			}
			break;
			
		default:
			break;
	}
}
