#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "scheduler.h"
#include "common.h"

#define TASKS_N     2
#define TICK_VAL    100
#define TIMEOUT     10000

static Sched_Task_t         tasks[ TASKS_N ];
static Sched_Scheduler_t    Sche;

void Init_500ms(void);
void Init_1000ms(void);
void Task_500ms(void);
void Task_1000ms(void);

int main( void )
{
    unsigned char TaskID1;
    unsigned char TaskID2;

    /* init the scheduler with two tasks and a tick time of 100ms and run for 10 seconds only */ 
    Sched_initScheduler ( &Sche, TASKS_N, TICK_VAL, TIMEOUT, tasks);

    /* register two task with their corresponding init functions and their periodicity, 100ms and 500ms*/ 
    TaskID1 = Sched_registerTask( &Sche, Init_500ms, Task_500ms, 500 );
    assert(TaskID1 != 0);
    TaskID2 = Sched_registerTask( &Sche, Init_1000ms, Task_1000ms, 1000 );
    assert(TaskID2 != 0);
    
    /* run the scheduler for the amount of time stablished in Sche.timeout */
    Sched_startScheduler( &Sche );
    
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
