/*
 * global.h
 *
 *  Created on: Oct 23, 2025
 *      Author: Dell
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define STATUS_LED_TIMER			0
#define NORMAL_TIMER 				1
#define CLOCK_TIMER					2
#define CLOCK_COUNTER				3
#define CONFIG_TIMER				4
#define DISPLAY_TIMER				5

#define RED_TIME					10
#define YEL_TIME					3
#define GRN_TIME					7
#define CONFIG_TIME					20
#define DISPLAY_TIME				2

enum traffic_light_state {
	INIT,

	// Auto mode
	AUTO_GRN_RED,
	AUTO_YEL_RED,
	AUTO_RED_GRN,
	AUTO_RED_YEL,

	// Manual mode
	MAN_GRN_RED,
	MAN_YEL_RED,
	MAN_RED_GRN,
	MAN_RED_YEL,

	// Config mode
	CFG_RED,
	CFG_YEL,
	CFG_GRN,

	// Vertical clock
	SEG0,
	SEG1,
	// Horizontal clock
	SEG2,
	SEG3
};

/////////////////////////////////////////////////////

extern uint8_t red_time;
extern uint8_t grn_time;
extern uint8_t yel_time;

extern uint8_t ver_clock;
extern uint8_t hor_clock;

extern uint8_t traffic_light_status;

#endif /* INC_GLOBAL_H_ */
