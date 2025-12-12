/*
 * scheduler.c
 *
 *  Created on: Nov 15, 2025
 *      Author: Dell
 */

#ifndef SRC_SCHEDULER_C_
#define SRC_SCHEDULER_C_

#include "scheduler.h"
#include <stdlib.h>

//#define SCH_MAX_TASKS	20
#define NO_TASK_ID 		0

static sTask* head = NULL;
static uint8_t nextID = 1;

static uint32_t SCH_Get_New_TaskID(void);
static sTask* SCH_Create_Node(void (*p_function)(), uint32_t DELAY, uint32_t PERIOD);
static void SCH_Free_Node(sTask *node);
static void SCH_Insert_Task_Sorted(sTask *newNode);

void SCH_Init(void) {
	head = NULL;
	nextID = 1;
}

void SCH_Update(void) {
    if (head != NULL && head->p_task != NULL) {
        if (head->RunMe == 0) {
            if (head->Delay > 0) {
                head->Delay--;
            }

            if (head->Delay == 0) {
                head->RunMe = 1;
            }
        }
    }
}

uint32_t SCH_Add_Task(void (*p_function)(), uint32_t DELAY, uint32_t PERIOD) {
    if (p_function == NULL) {
        return NO_TASK_ID;
    }

    uint32_t delay_ticks = DELAY;
    uint32_t period_ticks = PERIOD;

    sTask *newNode = SCH_Create_Node(p_function, delay_ticks, period_ticks);
    if (newNode == NULL) {
        return NO_TASK_ID;
    }

    SCH_Insert_Task_Sorted(newNode);

    return newNode->TaskID;
}

void SCH_Dispatch_Tasks(void) {
    if (head != NULL && head->RunMe > 0) {
        if (head->p_task != NULL) {
            head->p_task();
        }

        uint32_t period_ticks = head->Period;
        void (*taskFunc)(void) = head->p_task;

        sTask *temp = head;
        head = head->next;
        SCH_Free_Node(temp);

        if (period_ticks > 0) {
            uint32_t period_ms = period_ticks;
            SCH_Add_Task(taskFunc, period_ms, period_ms);
        }
    }

    __WFI();
}

uint8_t SCH_Delete_Task(uint32_t TASK_ID) {
    if (TASK_ID == NO_TASK_ID || head == NULL) {
        return 0;
    }

    sTask *prev = NULL;
    sTask *current = head;

    while (current != NULL) {
        if (current->TaskID == TASK_ID) {
            if (current->next != NULL) {
                current->next->Delay += current->Delay;
            }

            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }

            SCH_Free_Node(current);
            return 1;
        }
        prev = current;
        current = current->next;
    }

    return 0;
}

void SCH_Clear_All_Tasks(void) {
    while (head != NULL) {
        sTask *temp = head;
        head = head->next;
        SCH_Free_Node(temp);
    }
}

static uint32_t SCH_Get_New_TaskID(void) {
    uint32_t id = nextID++;

    // Skip NO_TASK_ID value
    if (nextID == NO_TASK_ID) {
        nextID = 1;
    }

    return id;
}

static sTask* SCH_Create_Node(void (*pFunction)(void), uint32_t Delay, uint32_t Period) {
    sTask *newNode = (sTask*)malloc(sizeof(sTask));

    if (newNode != NULL) {
        newNode->p_task = pFunction;
        newNode->Delay = Delay;
        newNode->Period = Period;
        newNode->TaskID = SCH_Get_New_TaskID();
        newNode->RunMe = (Delay == 0) ? 1 : 0;
        newNode->next = NULL;
    }

    return newNode;
}

static void SCH_Free_Node(sTask *node) {
    if (node != NULL) {
        free(node);
    }
}

static void SCH_Insert_Task_Sorted(sTask *newNode) {
    if (newNode == NULL) {
        return;
    }

    if (head == NULL) {
        head = newNode;
        return;
    }

    if (newNode->Delay < head->Delay) {
        head->Delay -= newNode->Delay;
        newNode->next = head;
        head = newNode;
        return;
    }

    sTask *current = head;
    uint32_t accumulatedDelay = head->Delay;

    while (current->next != NULL) {
        uint32_t nextAccumulatedDelay = accumulatedDelay + current->next->Delay;

        if (newNode->Delay < nextAccumulatedDelay) { //insertion point
            // calculate delay
            newNode->Delay = newNode->Delay - accumulatedDelay;
            // Adjust next node's relative Delay
            current->next->Delay = nextAccumulatedDelay - (accumulatedDelay + newNode->Delay);

            // Insert node
            newNode->next = current->next;
            current->next = newNode;
            return;
        }

        accumulatedDelay = nextAccumulatedDelay;
        current = current->next;
    }

    // Insert at end of list
    newNode->Delay = newNode->Delay - accumulatedDelay;
    current->next = newNode;
}

#endif /* SRC_SCHEDULER_C_ */
