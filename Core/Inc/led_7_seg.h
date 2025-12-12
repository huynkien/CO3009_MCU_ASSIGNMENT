/*
 * LED74HC595.h
 *
 *  Created on: Dec 10, 2025
 *      Author: Dell
 */

#ifndef INC_LED_7_SEG_H_
#define INC_LED_7_SEG_H_

#include"spi.h"
#include "gpio.h"

#define EMPTY 11



void led7_init();
void led7_write_number(uint8_t tl1, uint8_t tl2);

#endif /* INC_LED_7_SEG_H_ */
