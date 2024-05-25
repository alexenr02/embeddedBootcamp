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
#include <stdbool.h>
#include "scheduler.h"
#include "common.h"
#include "rtc.h"

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

void Sched_initScheduler( Sched_Scheduler_t* scheduler, uint8_t tasks, uint32_t tick, uint32_t timeout, Sched_Task_t* taskPtr, uint8_t timers, Sched_Timer_t* timerPtr  ) {
    scheduler->tick = tick;
    scheduler->tasks = tasks;
    scheduler->timeout = timeout;
    scheduler->taskPtr = taskPtr;
    scheduler->tasksCount = 0;
    scheduler->timers = timers;
    scheduler->timerPtr = timerPtr;
    scheduler->timersCount = 0;
    printf( "Scheduler initialized succesfully\n\n" );
}

uint8_t Sched_registerTask( Sched_Scheduler_t* scheduler, void (*initPtr)(void), void(*taskPtr)(void), uint32_t period ) {
    uint8_t taskId;
    if ( period < scheduler->tick || period % scheduler->tick != 0 || initPtr == NULL || taskPtr == NULL || scheduler->tasksCount >= scheduler->tasks) {
        printf("\nError: Period smaller than scheduler tick or not a factor or NULL ptr to function\n");
        return FALSE;
    }

    initPtr();
    printf("\n\n\n");
    taskId = scheduler->tasksCount;
    scheduler->taskPtr[taskId].initFunc = initPtr;
    scheduler->taskPtr[taskId].taskFunc = taskPtr;
    scheduler->taskPtr[taskId].period = period;
    scheduler->taskPtr[taskId].elapsed = 0;
    scheduler->taskPtr[taskId].startFlag = TRUE;
    scheduler->taskPtr[taskId].taskId = taskId + 1;
    scheduler->tasksCount++;
    PRINT_PARAMS("task number: %d, period: %d \n\n",scheduler->taskPtr[taskId].taskId, scheduler->taskPtr[taskId].period );
    return scheduler->taskPtr[taskId].taskId;
}


uint8_t Sched_startTask ( Sched_Scheduler_t *scheduler, uint8_t task ) {
    uint8_t flagOn = TRUE;
    
    if ( (scheduler->tasksCount < task) || (task < 1)  ) {
        flagOn = 0;
    }

    scheduler->taskPtr[task-1].startFlag = flagOn;

    return flagOn;
}

uint8_t Sched_stopTask( Sched_Scheduler_t *scheduler, uint8_t task ) {
    uint8_t flagOn = FALSE;
    
    if ( (scheduler->tasksCount < task) || (task < 1)  ) {
        flagOn = 0;
    }

    scheduler->taskPtr[task-1].startFlag = flagOn;

    return flagOn;
}

uint8_t Sched_periodicTask( Sched_Scheduler_t *scheduler, uint8_t task , uint32_t period ) {
    if ( period < scheduler->tick || period % scheduler->tick != 0 ) {
        return FALSE;
    }
    uint32_t lastPeriod = scheduler->taskPtr[task].period;
    scheduler->taskPtr[task].period = period;
    printf(" Task number %d changed its period from %d to %d successfully\n", task, lastPeriod, period);
    return TRUE;
}

uint8_t Sched_startScheduler( Sched_Scheduler_t *scheduler ) {
    

    bool tickCounterFlag = FALSE;               // Indicate if a tick period is reached
    bool timeOutFlag = FALSE;                   // Indicate if the scheduler reaches the general timeout
    bool stopTimer = FALSE;                     // Flag to stop the timer(s)
    
    long generalTickStartTime = milliseconds(); // Scheduler start time 
    long generalTickLastTime = milliseconds();  // Scheduler last time since last computer tick
    long generalTickCurrentTime = 0;            // Scheduler current time
    long generalTickCheckerAccumulator = 0;     // Scheduler elapsed time accumulator that is erased on every scheduler tick
    long generalTickElapsedTime = 0;            // Scheduler elapsed time since last computer tick

    if ( scheduler->timerPtr != NULL ) {
        PRINT("\n\n-------------- Registered timer info-----------------------\n\n");
        PRINT_PARAMS(" Timer %d, timeout: %d, count: %d, timer status: %d, current timer add: %x \n\n",0,currentTimer[0].timeout, currentTimer[0 ].count, currentTimer[0 ].startFlag, currentTimer);
        PRINT("-------------------------------------------------------");
        PRINT("\n\n\n");
    }

    while (timeOutFlag == FALSE) {

        generalTickCurrentTime = milliseconds();
        generalTickElapsedTime = generalTickCurrentTime - generalTickLastTime;
        generalTickCheckerAccumulator += generalTickCurrentTime - generalTickLastTime;
        generalTickLastTime = generalTickCurrentTime;   

        /* Activates the flag when on every tick */
        tickCounterFlag = FALSE;
        if(generalTickCheckerAccumulator > scheduler->tick) {
            generalTickCheckerAccumulator = 0;
            tickCounterFlag = TRUE;
        }

        /* Check if the tasks are on time to execute them */
        for( uint8_t i = 0; i < scheduler->tasksCount; i++ ) {
            Sched_Task_t *currentTask = &(scheduler->taskPtr[i]);
            currentTask->elapsed += generalTickElapsedTime;
            if (currentTask->elapsed >= currentTask->period && currentTask->startFlag == TRUE) {
                currentTask->taskFunc();
                currentTask->elapsed=0;
            }
            
        }

        /* If there are any timer, start, continue or stop counting */
        if ( scheduler->timerPtr != NULL ) {
            for( uint8_t i = 0; i < scheduler->timersCount; i++ ) {
                Sched_Timer_t *currentTimer = scheduler->timerPtr;
                if( tickCounterFlag == TRUE && currentTimer[i].startFlag == TRUE) {
                    currentTimer[i].count--;
                    if(currentTimer[i].count == 0) {
                        Sched_stopTimer(scheduler, i+1);
                        if(currentTimer[i].callbackPtr != NULL) {
                            currentTimer[i].callbackPtr();
                        }
                    }
                } 
            }
        }

        /* Check if the scheduler reached its timeout */
        if( (generalTickCurrentTime - generalTickStartTime) >= scheduler->timeout ) {
            timeOutFlag = TRUE;
            printf("\n\n Timeout... \n\n");
        }
    }
}

uint8_t  Sched_registerTimer( Sched_Scheduler_t *scheduler, uint32_t timeout, void (*callbackPtr)(void) ) {
    
    uint8_t timerId = scheduler->timersCount;

    if ( timeout < scheduler->tick || timeout % scheduler->tick != 0 || timerId >= scheduler->timers) {
        return FALSE;
    }
    Sched_Timer_t *currentTimer = scheduler->timerPtr;
    currentTimer[timerId].timeout = timeout;
    currentTimer[timerId].count = timeout/scheduler->tick;
    currentTimer[timerId].startFlag = FALSE;
    currentTimer[timerId].runFlag = FALSE;
    currentTimer[timerId].callbackPtr = callbackPtr;

    timerId = ++scheduler->timersCount;
    return timerId;
}

uint8_t Sched_getTimer( Sched_Scheduler_t *scheduler, uint8_t timer ) {
    if ( timer <= scheduler->timers && scheduler->timersCount > 0 ) {
        return scheduler->timerPtr[scheduler->timersCount - 1].count;
    } else {
        return FALSE;
    }
}

uint8_t Sched_reloadTimer( Sched_Scheduler_t *scheduler, uint8_t timer, uint32_t timeout ) {
   /* timer is registered and it has a valid ID */
   if ( timer <= scheduler->timers && scheduler->timersCount > 0 ) {
        scheduler->timerPtr[timer - 1].count = timeout;
        scheduler->timerPtr[timer - 1].timeout = timeout;
        scheduler->timerPtr[timer - 1].startFlag = FALSE;
        scheduler->timerPtr[timer - 1].runFlag = FALSE;
        printf("Timer %d stopped and reloaded.\n\n", timer);
        return TRUE;
    } else {
        return FALSE;
    } 
}

uint8_t Sched_startTimer( Sched_Scheduler_t *scheduler, uint8_t timer ) {
    /* timer is registered and it has a valid ID */
    if ( timer <= scheduler->timers && scheduler->timersCount > 0 ) {
        scheduler->timerPtr[timer - 1].startFlag = TRUE;
        scheduler->timerPtr[timer - 1].count = (scheduler->timerPtr[timer - 1].timeout)/scheduler->tick;

        //printf("\nTimer %d reloaded and activated succesfully. \n\n", timer);
        return TRUE;
    } else {
        return FALSE;
    }
}

uint8_t Sched_stopTimer( Sched_Scheduler_t *scheduler, uint8_t timer ) {
    /* timer is registered and it has a valid ID */
    if ( timer <= scheduler->timers && scheduler->timersCount > 0 ) {
        scheduler->timerPtr[timer - 1].startFlag = FALSE;
        //printf("\ntimer %d stopped\n", timer); //Imprimir esto causa bug de date = 0 en el timer 2, why?????
        return TRUE;
    } else {
        return FALSE;
    }
}

//TODO test functions isbuffer empty and readData
/********************************************************************************
 * Private Function Definitions
 *******************************************************************************/



