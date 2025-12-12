/*
 * scheduler.h
 *
 *  Created on: Nov 15, 2025
 *      Author: Dell
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "tim.h"
#include "stdint.h"
#include "global.h"

typedef struct sTask {
	void (*p_task) (void);
	uint32_t TaskID;
	uint32_t Delay;
	uint32_t Period;
	uint8_t  RunMe;
	struct sTask* next;
} sTask;

void SCH_Init(void);
void SCH_Update(void);
uint32_t SCH_Add_Task(void (*p_function)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_Dispatch_Tasks(void);
uint8_t SCH_Delete_Task(uint32_t TASK_ID);
void SCH_Clear_All_Tasks(void);

#endif /* INC_SCHEDULER_H_ */
