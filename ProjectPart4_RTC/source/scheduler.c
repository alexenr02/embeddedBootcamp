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
    printf( "Scheduler initialized succesfully\n\n" );
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
    printf("task number: %d, period: %d \n\n",scheduler->taskPtr[taskId].taskId, scheduler->taskPtr[taskId].period );
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
    if ( period < scheduler->tick || period % scheduler->tick != 0 ) {
        return FALSE;
    }
    uint32_t lastPeriod = scheduler->taskPtr[task].period;
    scheduler->taskPtr[task].period = period;
    printf(" Task number %d changed its period from %d to %d successfully\n", task, lastPeriod, period);
    return TRUE;
}

uint8_t Sched_startScheduler( Sched_Scheduler_t *scheduler ) {
    long lastTime = milliseconds();
    long startTime = milliseconds();
    long endTime = 0;
    long currentTime = 0;
    long elapsedTime = 0;

    bool_t tickCounterFlag = FALSE;
    bool_t timeOutFlag = FALSE;
    bool_t stopTimer = FALSE;

    long generalTickStartTime = startTime;
    long generalTickLastTime = lastTime;
    long generalTickCurrentTime = 0;
    long generalTickElapsedTime = 0;


    Sched_Timer_t *currentTimer = scheduler->timerPtr;
    if ( currentTimer != NULL ) {
        PRINT("\n\n-------------- Registered timer info-----------------------\n\n");
        PRINT_PARAMS(" Timer %d, timeout: %d, count: %d, timer status: %d, current timer add: %x \n\n",0,currentTimer[0].timeout, currentTimer[0 ].count, currentTimer[0 ].startFlag, currentTimer);
        PRINT("-------------------------------------------------------");
        PRINT("\n\n\n");
    }

    while (timeOutFlag == FALSE) {
        currentTime = milliseconds();
        elapsedTime = currentTime - lastTime;
        lastTime = currentTime;
        
        generalTickCurrentTime = milliseconds();
        generalTickElapsedTime += generalTickCurrentTime - generalTickLastTime;
        generalTickLastTime = generalTickCurrentTime;
        tickCounterFlag = FALSE;
        if(generalTickElapsedTime > scheduler->tick) {
            generalTickElapsedTime = 0;
            tickCounterFlag = TRUE;
        }

        for( uint8_t i = 0; i < scheduler->tasksCount; i++ ) {
            Sched_Task_t *currentTask = &(scheduler->taskPtr[i]);
            currentTask->elapsed += elapsedTime;
            if (currentTask->elapsed >= currentTask->period && currentTask->startFlag == TRUE) {
                currentTask->taskFunc();
                currentTask->elapsed=0;
            }
            
        }
        if ( currentTimer != NULL ) {
            for( uint8_t i = 0; i < scheduler->timersCount; i++ ) {
                Sched_Timer_t *currentTimer = scheduler->timerPtr;
                if( tickCounterFlag == TRUE && currentTimer[i].startFlag == TRUE) {
                    if (currentTimer[i].runFlag == FALSE) {
                        printf("\n\ntimer %d running\n\n", i);
                        currentTimer[i].runFlag = TRUE;
                    }
                    currentTimer[i].count--;
                    if(currentTimer[i].count == 0) {
                        Sched_stopTimer(scheduler, i);
                    }
                } 
            }
        }
        if( (currentTime - startTime) >= scheduler->timeout ) {
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
    printf("Timer %d registered succesfully\n\n", timerId);

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
        scheduler->timerPtr[timer - 1].count = scheduler->timerPtr[timer - 1].timeout;

        printf("Timer %d activated succesfully. \n\n", timer);
        return TRUE;
    } else {
        return FALSE;
    }
}

uint8_t Sched_stopTimer( Sched_Scheduler_t *scheduler, uint8_t timer ) {
    /* timer is registered and it has a valid ID */
    if ( timer <= scheduler->timers && scheduler->timersCount > 0 ) {
        scheduler->timerPtr[timer - 1].startFlag = FALSE;
        printf("\ntimer %d stopped\n", timer);
        return TRUE;
    } else {
        return FALSE;
    }
}

//TODO test functions isbuffer empty and readData
/********************************************************************************
 * Private Function Definitions
 *******************************************************************************/



