/*
 * fsm.h
 *
 *  Created on: Oct 2, 2025
 *      Author: Dell
 */

#ifndef INC_AUTO_MODE_H_
#define INC_AUTO_MODE_H_

#include "main.h"
#include "button.h"
#include "global.h"
#include "i2c-lcd.h"

// Forward declarations to avoid circular dependency
void init_cfg_red(void);

void fsm_auto_traffic_light_run();
void init_auto_mode();
uint16_t get_clock_counter(void);  // Lấy giá trị clock counter để hiển thị

void disable_all_tfl();
void green_red();
void yellow_red();
void red_green();
void red_yellow();


#endif /* INC_AUTO_MODE_H_ */
