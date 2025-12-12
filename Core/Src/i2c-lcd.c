/*
 * i2c-lcd.c
 *
 *  Created on: Dec 12, 2025
 *      Author: Dell
 */

#include "i2c-lcd.h"
extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly

#define SLAVE_ADDRESS_LCD (0x27 << 1) // change this according to ur setup

void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_init (void) {
	lcd_send_cmd (0x33); /* set 4-bits interface */
	lcd_send_cmd (0x32);
	HAL_Delay(50);
	lcd_send_cmd (0x28); /* start to set LCD function */
	HAL_Delay(50);
	lcd_send_cmd (0x01); /* clear display */
	HAL_Delay(50);
	lcd_send_cmd (0x06); /* set entry mode */
	HAL_Delay(50);
	lcd_send_cmd (0x0c); /* set display to on */
	HAL_Delay(50);
	lcd_send_cmd (0x02); /* move cursor to home and set data address to 0 */
	HAL_Delay(50);
	lcd_send_cmd (0x80);
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

void lcd_send_integer(uint8_t number) {
	char buf[4];
	uint8_t i = 0;

	if (number == 0){
		lcd_send_data('0');
		return;
	}

	while (number > 0) {
		buf[i++] = (number % 10) + '0';
		number /= 10;
	}

	while(i > 0) {
		lcd_send_data(buf[--i]);

	}
}

void lcd_clear_display (void)
{
	lcd_send_cmd (0x01); //clear display
	HAL_Delay(2);        // Clear command needs ~2ms to execute
}

void lcd_goto_XY (int row, int col)
{
	uint8_t pos_Addr;
	if(row == 0)
	{
		pos_Addr = 0x80 + col;        // Row 0: address 0x00-0x0F
	}
	else
	{
		pos_Addr = 0x80 | (0x40 + col); // Row 1: address 0x40-0x4F
	}
	lcd_send_cmd(pos_Addr);
}



