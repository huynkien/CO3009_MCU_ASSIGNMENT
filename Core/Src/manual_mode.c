/*
 * manual_mode.c
 *
 *  Created on: Nov 3, 2025
 *      Author: Dell
 */

#include "manual_mode.h"

void fsm_manual_traffic_light_run() {
	switch (traffic_light_status) {
		case MAN_GRN_RED:
			man_green_red();

			ver_clock = 5;
			hor_clock = 5;

			if (isButtonPressed(&button1)) {
				traffic_light_status = MAN_YEL_RED;
			}
			
			if (isButtonPressed(&button0)) {
				init_auto_mode();
			}
			break;
			
		case MAN_YEL_RED:
			man_yellow_red();
			ver_clock = 6;
			hor_clock = 6;

			if (isButtonPressed(&button1)) {
				traffic_light_status = MAN_RED_GRN;
			}
			
			if (isButtonPressed(&button0)) {
				init_auto_mode();
			}
			break;
			
		case MAN_RED_GRN:
			man_red_green();
			ver_clock = 7;
			hor_clock = 7;

			if (isButtonPressed(&button1)) {
				traffic_light_status = MAN_RED_YEL;
			}
			
			if (isButtonPressed(&button0)) {
				init_auto_mode();
			}
			break;
			
		case MAN_RED_YEL:
			man_red_yellow();
			ver_clock = 8;
			hor_clock = 8;

			if (isButtonPressed(&button1)) {
				traffic_light_status = MAN_GRN_RED;
			}
			
			if (isButtonPressed(&button0)) {
				init_auto_mode();
			}
			break;
			
		default:
			break;
	}
}

void man_green_red() {
//	lcd_clear_display();
	lcd_goto_XY(0, 0);
	lcd_send_string("MODE: MANUAL");
	lcd_goto_XY(1, 0);
	lcd_send_string("GREEN - RED   ");


	HAL_GPIO_WritePin(TL0_0_GPIO_Port, TL0_0_Pin, 1);
	HAL_GPIO_WritePin(TL0_1_GPIO_Port, TL0_1_Pin, 0);

	HAL_GPIO_WritePin(TL1_0_GPIO_Port, TL1_0_Pin, 1);
	HAL_GPIO_WritePin(TL1_1_GPIO_Port, TL1_1_Pin, 1);
}
void man_yellow_red() {
//	lcd_clear_display();
	lcd_goto_XY(0, 0);
	lcd_send_string("MODE: MANUAL");
	lcd_goto_XY(1, 0);
	lcd_send_string("YELLOW - RED  ");

	HAL_GPIO_WritePin(TL0_0_GPIO_Port, TL0_0_Pin, 0);
	HAL_GPIO_WritePin(TL0_1_GPIO_Port, TL0_1_Pin, 1);

	HAL_GPIO_WritePin(TL1_0_GPIO_Port, TL1_0_Pin, 1);
	HAL_GPIO_WritePin(TL1_1_GPIO_Port, TL1_1_Pin, 1);
}
void man_red_green() {
//	lcd_clear_display();
	lcd_goto_XY(0, 0);
	lcd_send_string("MODE: MANUAL");
	lcd_goto_XY(1, 0);
	lcd_send_string("RED - GREEN   ");

	HAL_GPIO_WritePin(TL0_0_GPIO_Port, TL0_0_Pin, 1);
	HAL_GPIO_WritePin(TL0_1_GPIO_Port, TL0_1_Pin, 1);

	HAL_GPIO_WritePin(TL1_0_GPIO_Port, TL1_0_Pin, 1);
	HAL_GPIO_WritePin(TL1_1_GPIO_Port, TL1_1_Pin, 0);
}
void man_red_yellow() {
//	lcd_clear_display();
	lcd_goto_XY(0, 0);
	lcd_send_string("MODE: MANUAL");
	lcd_goto_XY(1, 0);
	lcd_send_string("RED - YELLOW  ");

	// Vertical road
	HAL_GPIO_WritePin(TL0_0_GPIO_Port, TL0_0_Pin, 1);
	HAL_GPIO_WritePin(TL0_1_GPIO_Port, TL0_1_Pin, 1);

	HAL_GPIO_WritePin(TL1_0_GPIO_Port, TL1_0_Pin, 0);
	HAL_GPIO_WritePin(TL1_1_GPIO_Port, TL1_1_Pin, 1);
}
