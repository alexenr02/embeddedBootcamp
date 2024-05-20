#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "common.h"
#include "scheduler.h"
#include "queue.h"
#include "rtc.h"

#define TASKS_N     1
#define TICK_VAL    100
#define TIMERS_N    2

static Sched_Task_t         tasks[ TASKS_N ];
static Sched_Scheduler_t    Sche;
static Rtcc_Clock_t         rtccClock;
static Queue_Queue_t        rtccQueue;
static Sched_Timer_t        timers[ TIMERS_N ];
static unsigned char        TimerId;
static unsigned char        TimerId2;

void Init_500ms(void);
void Task_500ms(void);
void Init_Rtcc(void);
void Callback(void);
void Callback2(void);
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
    Sched_initScheduler( &Sche, TASKS_N, TICK_VAL, 30000, tasks, TIMERS_N, timers );

    /*register two task with thier corresponding init fucntions and their periodicyt, 100ms and 500ms*/
    if ( Sched_registerTask( &Sche, Init_500ms, Task_500ms, 500 ) == FALSE ) {
        printf("\nError:Could not register task.\n");
        return 0;
    }
    
    TimerId     = Sched_registerTimer( &Sche, 1000u, Callback );
    if ( TimerId == FALSE ) {
        printf("\nError:Could not register timer.\n");
        return 0;
    }

    TimerId2     = Sched_registerTimer( &Sche, 5000u, Callback2);
    if ( TimerId2 == FALSE ) {
        printf("\nError:Could not register timer.\n");
        return 0;
    }

    Init_Rtcc();

    if ( Sched_startTimer(&Sche, TimerId) == FALSE ) {
        printf("\nError: Could not start timer.\n");
    }

    if ( Sched_startTimer(&Sche, TimerId2) == FALSE ) {
        printf("\nError: Could not start timer.\n");
    }
    
    /*run the scheduler for the mount of time stablished in Sche.timeout*/
    Sched_startScheduler( &Sche );

    return 0;
}

/**
 * @brief   Init function for RTC
 * Print a message to the console to indicate that the task is running
*/
void Init_Rtcc(void)
{
    Rtcc_clockInit( &rtccClock );
    Rtcc_setTime( &rtccClock, 12, 30, 0 );
    Rtcc_setDate( &rtccClock, 24, 6, 1984 );
    printf("Init RTC\n");
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
 * @brief   500ms task
 *
 * Read the queue and print the time and date if a new message arrives
*/
void Task_500ms(void)
{
    Message msgToRead;
    printf("\n\t\t\t\t\t\t\t|---------------------------------------|");
    printf("\n\t\t\t\t\t\t\t|\tRunning <- Task 500 ms\t\t|");
    /* Query if a new message arrive from the queue */
    if( Queue_isQueueEmpty( &rtccQueue ) == FALSE )
    {
        /* Read the message in the queue */
        if(Queue_readData( &rtccQueue, &msgToRead ) == FALSE) {
            printf("\nError reading from the queue\n");
        } else {
            printf("\n\t\t\t\t\t\t\t|\tData Received:\t\t\t|");
            switch (msgToRead.msg) {
                case DATE:
                    printf("\n\t\t\t\t\t\t\t|\tTask 500 ms: Date - %d/%d/%d\t|\n", msgToRead.day, msgToRead.month, msgToRead.year );
                    break;
                case HOUR:
                    printf("\n\t\t\t\t\t\t\t|\tTask 500 ms: Time - %d:%d:%d\t|\n", msgToRead.hour, msgToRead.minutes, msgToRead.seconds );
                    break;
                default:
                    break;
            }
        }
    }
    printf("\t\t\t\t\t\t\t|---------------------------------------|\n");
}

void Callback (void) {
    printf("\n|-----------------------------------------------|");
    printf("\n|\tRunning -> Callback                \t|\n|\tData To Send:\t\t\t\t|");
    Message msgToWrite;
    /*Clock periodic task */
    Rtcc_periodicTask( &rtccClock );
    /*get time and date and send time and date to 500ms task using a queue */
    Rtcc_getTime( &rtccClock, &msgToWrite.hour, &msgToWrite.minutes, &msgToWrite.seconds, &msgToWrite.msg );
    printf("\n|\tTime: %d:%d:%d\t\t\t\t|\n", msgToWrite.hour, msgToWrite.minutes, msgToWrite.seconds);
    Queue_writeData( &rtccQueue, &msgToWrite );
    Rtcc_getDate( &rtccClock, &msgToWrite.day, &msgToWrite.month, &msgToWrite.year, &msgToWrite.wday, &msgToWrite.msg );
    printf("|\tDate: %d/%d/%d\t\t\t\t|\n", msgToWrite.day, msgToWrite.month, msgToWrite.year);
    Queue_writeData( &rtccQueue, &msgToWrite );
    printf("|-----------------------------------------------|");
    
    Sched_startTimer( &Sche, TimerId );
}

void Callback2 (void) {
    //printf("\nexecuting callback 2\n");
    static int loop = 0;
    loop++;
    //printf("This is a counter from the timer callback2: %d \n", loop++);
    if ( loop == 1 ) {
        Rtcc_setTime( &rtccClock, 5, 5, 5 );
        Rtcc_setDate( &rtccClock, 25, 4, 1999 );
    }
    if ( loop == 2 ) {
        Rtcc_setTime( &rtccClock, 15, 15, 15 );
        Rtcc_setDate( &rtccClock, 15, 10, 2015 );
    }
    if ( loop == 3 ) {
        Rtcc_setTime( &rtccClock, 22, 25, 25 );
        Rtcc_setDate( &rtccClock, 25, 5, 2025 );
        loop = 0;
    }
    Sched_startTimer( &Sche, TimerId2 );
    //printf("\nfinish callback 2\n");
}