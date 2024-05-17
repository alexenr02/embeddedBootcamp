#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "scheduler.h"
#include "common.h"
#include "rtc.h"

#define TASKS_N     2
#define TIMERS_N    1
#define TICK_VAL    100
#define TIMEOUT     10000

static Sched_Task_t         tasks[ TASKS_N ];
static Sched_Timer_t        timers[ TIMERS_N ];
static Rtcc_Clock_t         rtccClock;
static Sched_Scheduler_t    Sche;
static unsigned char        TimerId;

void Init_500ms(void);
void Init_1000ms(void);
void Task_500ms(void);
void Task_1000ms(void);
void Callback(void);

int main( void )
{  
    unsigned char TaskId; 

    /* Init the scheduler with two tasks and a tick time of 100mS and run for 10 seconds only */
    Sched_initScheduler ( &Sche, TASKS_N, TICK_VAL, TIMEOUT, tasks, TIMERS_N, timers );
    /*  */
    TaskId      = Sched_registerTask( &Sche, Init_500ms, Task_500ms, 500 );
    TimerId     = Sched_registerTimer( &Sche, 1000u, Callback );
    PRINT_PARAMS("Task ID: %d, timer ID: %d \n\n", TaskId, TimerId);
    TaskId      = Sched_registerTask( &Sche, Init_1000ms, Task_1000ms, 1000 );


    Sched_startTimer(&Sche, TimerId);
    Sched_startScheduler( &Sche );
}

void Init_500ms(void) {
    printf("\nInit task 500 milisecond\n");
}

void Task_500ms(void) {
    static int loop = 0;
    printf("\nThis is a counter from task 500ms: %d", loop++);
}

void Init_1000ms(void) {
    Rtcc_clockInit( &rtccClock );
    assert(Rtcc_setTime( &rtccClock, 23, 59, 55 ));
    assert(Rtcc_setDate( &rtccClock, 31, 12, 2023 ));
    printf("\nInit task 1000 millisecond\n");
}
void Task_1000ms(void) {
    static int loop = 0;
    Rtcc_periodicTask(&rtccClock);
    printf("\nThis is a counter from task 1000ms: %d", loop++);
}

void Callback (void) {
    static int loop = 0;
    printf("\nThis is a counter from the timer callback: %d \n", loop++);
    Sched_startTimer( &Sche, TimerId );
}
