/**
 * \file buffer.c
 * 
 * Functions call necessary for the circular buffer. The circular buffer will
 * store a specific amount of values and it is operated by a FIFO logic.
 * 
*/

/********************************************************************************
 * Header Files
 *******************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "scheduler.h"
#include "common.h"

/********************************************************************************
 * Variable Declarations
 *******************************************************************************/

/********************************************************************************
 * Private Function Prototypes
 *******************************************************************************/

/********************************************************************************
 * Public Function
 *******************************************************************************/

long milliseconds (void) {
    return clock() / ( CLOCKS_PER_SEC / 1000 );
}

void Sched_initScheduler( Sched_Scheduler_t* scheduler, uint8_t tasks, uint32_t tick, uint32_t timeout, Sched_Task_t* taskPtr  ) {
    scheduler->tick = tick;
    scheduler->tasks = tasks;
    scheduler->timeout = timeout;
    scheduler->taskPtr = taskPtr;
    scheduler->tasksCount = 0;
}

uint8_t Sched_registerTask( Sched_Scheduler_t* scheduler, void (*initPtr)(void), void(*taskPtr)(void), uint32_t period ) {
    uint8_t taskId;
    if ( period < scheduler->tick || period % scheduler->tick != 0 ) {
        return FALSE;
    }


    if( scheduler->tasksCount > scheduler->tasks) {
        return FALSE;
    }
    initPtr();
    taskId = scheduler->tasksCount;
    scheduler->taskPtr[taskId].initFunc = initPtr;
    scheduler->taskPtr[taskId].taskFunc = taskPtr;
    scheduler->taskPtr[taskId].period = period;
    scheduler->taskPtr[taskId].elapsed = 0;
    scheduler->taskPtr[taskId].startFlag = TRUE;
    scheduler->taskPtr[taskId].taskId = taskId + 1;
    scheduler->tasksCount++;
    return scheduler->taskPtr[taskId].taskId;
}



uint8_t Sched_startTask ( Sched_Scheduler_t *scheduler, uint8_t task ) {
    uint8_t flagOn = TRUE;
    
    //if ( (scheduler->tasksCount < task) || (task < 1)  ) {
       // flagOn = 0;
    //}

    scheduler->taskPtr[task].startFlag = flagOn;

    return flagOn;
}

uint8_t Sched_stopTask( Sched_Scheduler_t *scheduler, uint8_t task ) {
    uint8_t flagOn = FALSE;
    
    /*if ( (scheduler->tasksCount < task) || (task < 1)  ) {
        flagOn = 0;
    }*/

    scheduler->taskPtr[task].startFlag = flagOn;

    return flagOn;
}

uint8_t Sched_periodicTask( Sched_Scheduler_t *scheduler, uint8_t task , uint32_t period ) {

}

uint8_t Sched_startScheduler( Sched_Scheduler_t *scheduler ) {
    long lastTime = milliseconds();
    long startTime = milliseconds();
    long currentTime = 0;
    long elapsedTime = 0;
    bool_t timeOutFlag = FALSE;
    while (timeOutFlag == FALSE) {
        currentTime = milliseconds();
        elapsedTime = currentTime - lastTime;
        lastTime = currentTime;

        for( uint8_t i = 0; i < scheduler->tasksCount; i++ ) {
            Sched_Task_t *currentTask = &(scheduler->taskPtr[i]);
            currentTask->elapsed += elapsedTime;

            if (currentTask->elapsed >= currentTask->period && currentTask->startFlag == TRUE) {
                currentTask->taskFunc();
                currentTask->elapsed=0;
            }
        }
        if( (currentTime - startTime) >= scheduler->timeout ) {
            timeOutFlag = TRUE;
        }
        if ( (currentTime - startTime) >= (scheduler->timeout/2) ) {
            Sched_stopTask(scheduler, 0);
        }
        if ( (currentTime - startTime) >= (7000) ) {
            Sched_startTask(scheduler, 0);
        }
    }
}



//TODO test functions isbuffer empty and readData
/********************************************************************************
 * Private Function Definitions
 *******************************************************************************/



