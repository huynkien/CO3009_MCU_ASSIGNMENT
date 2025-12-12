/*
 * button.h
 *
 *  Created on: Oct 23, 2025
 *      Author: Dell
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include "global.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET

struct ButtonStruct {
	uint8_t 		keyBuffer[4]; //New data [0], old data [2]
	uint16_t 		timeOutForPressed;
	uint8_t 		isPressed;
	uint8_t 		isLongPressed;
	GPIO_TypeDef 	*PORT;
	uint16_t 		PIN;
};

extern struct ButtonStruct button0;
extern struct ButtonStruct button1;
extern struct ButtonStruct button2;
//extern struct ButtonStruct button3;

void getKeyInput(struct ButtonStruct* button);
uint8_t isButtonPressed(struct ButtonStruct *button);
uint8_t isButtonLongPressed(struct ButtonStruct *button);
void resetButton(struct ButtonStruct *button);


#endif /* INC_BUTTON_H_ */
