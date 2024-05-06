#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "scheduler.h"
#include "common.h"

#define TASKS_N     1
#define TIMERS_N    1
#define TICK_VAL    100
#define TIMEOUT     10000

static Sched_Task_t         tasks[ TASKS_N ];
static Sched_Timer_t        timers[ TIMERS_N ];
static Sched_Scheduler_t    Sche;
static unsigned char        TimerId;

void Init_500ms(void);
void Task_500ms(void);
void Callback(void);

int main( void )
{  
    unsigned char TaskId; 

    /* Init the scheduler with two tasks and a tick time of 100mS and run for 10 seconds only */
    Sched_initScheduler ( &Sche, TASKS_N, TICK_VAL, TIMEOUT, tasks, TIMERS_N, timers );
    printf("\n\n\n");
    printf( "Scheduler initialized succesfully\n\n" );
    /* register two tasks with their corresponding init functions and their periodicity, 100 mS and 500 mS */
    TaskId      = Sched_registerTask( &Sche, Init_500ms, Task_500ms, 500 );
    TimerId     = Sched_registerTimer( &Sche, 6000u, Callback );
    printf("Task ID: %d, timer ID: %d \n\n", TaskId, TimerId);


    Sched_startTimer(&Sche, TimerId);
    Sched_startScheduler( &Sche );
}

void Init_500ms(void) {
    printf("Init task 500 milisecond\n");
}

void Task_500ms(void) {
    static int loop = 0;
    printf("\nThis is a counter from task 500ms: %d", loop++);
}

void Callback (void) {
    static int loop = 0;
    printf("This is a counter from the timer callback: %d \n", loop++);
    Sched_startTimer( &Sche, TimerId );
}
