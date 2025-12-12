/*
 * led_7_seg.c
 *
 *  Created on: Dec 9, 2025
 *      Author: qwein
 */
#include "led_7_seg.h"

 uint8_t number_map[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0xFF};
//							   0	 1	   2	 3	   4	...                            turn off number
uint8_t led7_digit[] = {0, 0, 0, 0};
uint32_t spi_data = 0xffffffff;

void led7_init() {
	HAL_GPIO_WritePin(LOAD_GPIO_Port, LOAD_Pin, 1);
}

void led7_set_digit(uint8_t digit, uint8_t number) {
	uint32_t mask = 0xff;
	uint8_t code_num = ~number_map[number]; //common anode
	spi_data &= ~(mask << (digit * 8));
	spi_data |= (uint32_t)code_num << (digit * 8);
}
void led7_write_number(uint8_t tl1, uint8_t tl2) {
	uint8_t ten1 = tl1 / 10;
	uint8_t unit1 = tl1 % 10;
	uint8_t ten2 = tl2 / 10;
	uint8_t unit2 = tl2 % 10;
	if (tl1 % 10 == 0) {
		ten1 = EMPTY;
	}
	if (tl2 % 10 == 0) {
		ten2 = EMPTY;
	}
	led7_set_digit(0, unit1);
	led7_set_digit(1, ten1);
	led7_set_digit(2, unit2);
	led7_set_digit(3, ten2);
	HAL_GPIO_WritePin(LOAD_GPIO_Port, LOAD_Pin, 0);
	HAL_SPI_Transmit(&hspi2, (uint8_t*)&spi_data, 4, 100);
	HAL_GPIO_WritePin(LOAD_GPIO_Port, LOAD_Pin, 1);
}


