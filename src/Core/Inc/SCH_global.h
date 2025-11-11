/*
 * SCH_global.h
 *
 *  Created on: Nov 25, 2024
 *      Author: Admin
 */

#include "main.h"

#ifndef INC_SCH_GLOBAL_H_
#define INC_SCH_GLOBAL_H_

typedef struct {
	// Pointer to the task (must be a ’void (void) ’ function)
	void (*pTask)(void);
	// Delay (ticks) until the function will (next) be run
	uint32_t Delay;
	// Interval (ticks) between subsequent runs.
	uint32_t Period;
	// Incremented (by scheduler) when task is due to execute
	uint8_t RunMe;
	//This is a hint to solve the question below.
	uint32_t TaskID;
} sTask;

void SCH_Init(void);
void SCH_Update(void);
unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int DELAY,
		unsigned int PERIOD);
void SCH_Dispatch_Tasks(void);
unsigned char SCH_Delete_Task(const unsigned char TASK_INDEX);
void SCH_Go_To_Sleep();
void SCH_Report_Status(void);

// MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCH_MAX_TASKS	40
#define NO_TASK_ID	0
sTask SCH_tasks_G[SCH_MAX_TASKS];

//define errors
#define ERROR_SCH_TOO_MANY_TASKS	1
#define ERROR_SCH_CANNOT_DELETE_TASK	2
#define RETURN_ERROR	3
#define RETURN_NORMAL	4

extern unsigned char Error_code_G;

#endif /* INC_SCH_GLOBAL_H_ */
