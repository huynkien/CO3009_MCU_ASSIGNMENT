/*
 * button.c
 *
 *  Created on: Oct 23, 2025
 *      Author: Dell
 */

#include "button.h"


struct ButtonStruct button0 = {
		{NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE},
		150,
		0,
		0,
		BTN0_GPIO_Port,
		BTN0_Pin
};

struct ButtonStruct button1 = {
		{NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE},
		150,
		0,
		0,
		BTN1_GPIO_Port,
		BTN1_Pin
};

struct ButtonStruct button2 = {
		{NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE},
		150,
		0,
		0,
		BTN2_GPIO_Port,
		BTN2_Pin
};

//struct ButtonStruct button3 = {
//		{NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE},
//		150,
//		0,
//		0,
//		BTN3_GPIO_Port,
//		BTN3_Pin
//};

void getKeyInput(struct ButtonStruct* button) {
	button->keyBuffer[2] = button->keyBuffer[1];
	button->keyBuffer[1] = button->keyBuffer[0];

	button->keyBuffer[0] = HAL_GPIO_ReadPin(button->PORT, button->PIN);

	if ((button->keyBuffer[0] == button->keyBuffer[1]) && (button->keyBuffer[1] == button->keyBuffer[2]))
	{
		if (button->keyBuffer[2] != button->keyBuffer[3])
		{
			button->keyBuffer[3] = button->keyBuffer[2];

			if (button->keyBuffer[3] == PRESSED_STATE)
			{
				button->timeOutForPressed = 150;
				button->isPressed = 1;
			}
		}
		else // button->keyBuffer[2] == button->keyBuffer[3]
		{
			--button->timeOutForPressed;
			if (button->timeOutForPressed <= 0)
			{
				button->timeOutForPressed = 150;
				if (button->keyBuffer[3] == PRESSED_STATE)
				{
					button->isLongPressed = 1;
				}
			}
		}
	}
}

uint8_t isButtonPressed(struct ButtonStruct *button) {
	if (button->isPressed == 1)
	{
		button->isPressed = 0;
		return 1;
	}
	return 0;
}

uint8_t isButtonLongPressed(struct ButtonStruct *button) {
	if (button->isLongPressed == 1)
	{
		button->isLongPressed = 0;
		return 1;
	}
	return 0;
}

void resetButton(struct ButtonStruct *button) {
	button->isPressed = 0;
	button->isLongPressed = 0;
}
