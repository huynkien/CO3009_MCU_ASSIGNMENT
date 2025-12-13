/*
 * global.h
 *
 *  Created on: Oct 23, 2025
 *      Author: Dell
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

// Software Timer indices
#define TIMER_STATE      0   // State duration timer (for auto mode state transitions)
#define TIMER_CLOCK      1   // 1-second clock timer (for countdown display)
#define TIMER_BLINK      2   // LED blink timer (for config mode)

// Time constants (in seconds)
#define RED_TIME					10
#define YEL_TIME					3
#define GRN_TIME					7

// Tick constants (task runs every 10ms, so 100 ticks = 1 second)
#define TICKS_PER_SECOND            1000
#define CONFIG_BLINK_TICKS          500   // 500ms blink period

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
