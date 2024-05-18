#include <stdio.h>
#include <stdint.h>
#include "common.h"
#include "scheduler.h"
#include "queue.h"
#include "rtc.h"

/**
 * @brief   message to be used for intercomunicate both tasks
*/
typedef struct _Message
{
    uint8_t hour;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t day;
    uint8_t wday;
    uint8_t month;
    uint16_t year;
} Message;

#define TASKS_N     2
#define TICK_VAL    100
#define TIMERS_N    1

static Sched_Task_t         tasks[ TASKS_N ];
static Sched_Scheduler_t    Sche;
static Rtcc_Clock_t         rtccClock;
static Queue_Queue_t        rtccQueue;
static Sched_Timer_t        timers[ TIMERS_N ];
static unsigned char        TimerId;

void Init_500ms(void);
void Init_1000ms(void);
void Task_500ms(void);
void Task_1000ms(void);
void Callback(void);
int main( void )
{
    unsigned char TaskId;
    static Message Messages[6u];

    /*create the queue to store as max 6 items*/
    rtccQueue.Buffer = Messages;
    rtccQueue.Elements = 6;
    rtccQueue.Size = sizeof( Message );
    Queue_initQueue( &rtccQueue );

    /*init the scheduler with two tasks and a tick time of 100ms and run for 10 seconds only*/
    Sched_initScheduler( &Sche, TASKS_N, TICK_VAL, 10000, tasks, 1, timers );
    
    /*register two task with thier corresponding init fucntions and their periodicyt, 100ms and 500ms*/
    Sched_registerTask( &Sche, Init_500ms, Task_500ms, 500 );
    Sched_registerTask( &Sche, Init_1000ms, Task_1000ms, 1000 );
    printf("\n\n\n");
    TimerId     = Sched_registerTimer( &Sche, 3000u, Callback );
    PRINT_PARAMS("Task ID: %d, timer ID: %d \n\n", TaskId, TimerId);


    Sched_startTimer(&Sche, TimerId);
    /*run the scheduler for the mount of time stablished in Sche.timeout*/
    Sched_startScheduler( &Sche );
    
    return 0;
}

/**
 * @brief   Init task for 500ms task
 * 
 * Print a message to the console to indicate that the task is running
*/
void Init_500ms(void)
{
    printf("Init task 500 millisecond\n");
}

/**
 * @brief   Init task for 1000ms task
 * 
 * Print a message to the console to indicate that the task is running
 * and init the clock to 12:30:00 24/6/1984
*/
void Init_1000ms(void)
{
    Rtcc_clockInit( &rtccClock );
    Rtcc_setTime( &rtccClock, 12, 30, 0 );
    Rtcc_setDate( &rtccClock, 24, 6, 1984 );
    printf("Init task 1000 millisecond\n");
}

/**
 * @brief   500ms task
 * 
 * Read the queue and print the time and date if a new message arrives
*/
void Task_500ms(void)
{ 
    Message msgToRead;
    static int loop = 0;
    printf("\nThis is a counter from task 500ms: %d", loop++);
    /* Query if a new message arrive from the queue */
    if( Queue_isQueueEmpty( &rtccQueue ) == 0 )
    {
        /* Read the message in the queue */
        Queue_readData( &rtccQueue, &msgToRead );
        printf("\nTask 500 ms: Time - %d:%d:%d\n", msgToRead.hour, msgToRead.minutes, msgToRead.seconds );
        printf("\nTask 500 ms: Date - %d/%d/%d\n", msgToRead.day, msgToRead.month, msgToRead.year );
    }
    printf("\nRunning: task 500 millisecond\n");
}

/**
 * @brief   1000ms task
 * 
 * Poll the Rtcc periodic task and get the time and date from the clock and send it to 
 * the 500ms task using a queue
*/
void Task_1000ms(void)
{
    static int loop = 0;
    printf("\nThis is a counter from task 1000ms: %d", loop++);
    printf("\nRunning: task 1000 millisecond\n");
    Message msgToWrite;
    /*Clock periodic task */
    Rtcc_periodicTask( &rtccClock );
    /*get time and date */
    Rtcc_getTime( &rtccClock, &msgToWrite.hour, &msgToWrite.minutes, &msgToWrite.seconds );
    Rtcc_getDate( &rtccClock, &msgToWrite.day, &msgToWrite.month, &msgToWrite.year, &msgToWrite.wday );
    /*send time and date to 500ms task using a queue */
    Queue_writeData( &rtccQueue, &msgToWrite );
    
}

void Callback (void) {
    static int loop = 0;
    printf("This is a counter from the timer callback: %d \n", loop++);
    Sched_startTimer( &Sche, TimerId );
}