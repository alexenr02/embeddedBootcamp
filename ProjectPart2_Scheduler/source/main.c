#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "scheduler.h"
#include "common.h"

#define TASKS_N     2
#define TICK_VAL    100

static Sched_Task_t         tasks[ TASKS_N ];
static Sched_Scheduler_t    Sche;

void Init_500ms(void);
void Init_1000ms(void);
void Task_500ms(void);
void Task_1000ms(void);

int main( void )
{/*
    unsigned char TaskID1;
    unsigned char TaskID2;

    /* init the scheduler with two tasks and a tick time of 100ms and run for 10 seconds only 
    Sche.tick = TICK_VAL;
    Sche.tasks = TASKS_N;
    Sche.timeout = 10000;
    Sche.taskPtr = tasks;
    Sched_initScheduler ( &Sche );

    /* register two task with their corresponding init functions and their periodicity, 100ms and 500ms 
    TaskID1 = Sched_registerTask( &Sche, Init_500ms, Task_500ms, 500 );
    TaskID2 = Sched_registerTask( &Sche, Init_1000ms, Task_1000ms, 1000);

    /* run the scheduler for the amount of time stablished in Sche.timeout 
    Sched_startScheduler( &Sche );
    */
    return 0;
    
}

void Init_500ms(void) {
    printf("Init task 500 milisecond\n");
}
void Init_1000ms(void) {
    printf("Init task 1000 milisecond\n");
}
void Task_500ms(void) {
    static int loop = 0;
    printf("\nThis is a counter from task 500ms: %d", loop++);
}
void Task_1000ms(void) {
    static int loop = 0;
    printf("\nThis is a counter from task 1000ms: %d", loop++);
} 
