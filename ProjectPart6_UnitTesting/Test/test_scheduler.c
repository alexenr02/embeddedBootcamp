#include "unity.h"
#include "scheduler.h"

#define TRUE    1
#define FALSE   0

#define TASKS_N         3
#define TICK_VAL        100
#define TASKS_PERIOD    500
#define TIMERS_N        3
#define SCHED_TIMEOUT   10000u


void Init_1(void);
void Task_1(void);
void Init_2(void);
void Task_2(void);
void Init_3(void);
void Task_3(void);
void Init_4(void);
void Task_4(void);

void setUp(void)
{
}

void tearDown(void)
{
}

/**
 * @brief   Test Sched_initScheduler function
 *      
 * The test verify that the scheduler is initialized correctly using a scheduler with 3 tasks, 3 timers and timeout of 10 seconds
 */
void test__Sched_initScheduler_tasks_timers( void )
{
    Sched_Scheduler_t    Sche;
    Sched_Task_t         tasks_array[ TASKS_N ];
    Sched_Timer_t        timers_array[ TIMERS_N ];

    Sched_initScheduler( &Sche, TASKS_N, TICK_VAL, SCHED_TIMEOUT, tasks_array, TIMERS_N, timers_array );

    TEST_ASSERT_EQUAL_PTR( tasks_array, Sche.taskPtr );
    TEST_ASSERT_EQUAL_PTR( timers_array, Sche.timerPtr );
    TEST_ASSERT_EQUAL( TASKS_N, Sche.tasks );
    TEST_ASSERT_EQUAL( TICK_VAL, Sche.tick );
    TEST_ASSERT_EQUAL( SCHED_TIMEOUT, Sche.timeout );
    TEST_ASSERT_EQUAL( 0, Sche.tasksCount );
    TEST_ASSERT_EQUAL( TIMERS_N, Sche.timers );
    TEST_ASSERT_EQUAL( 0, Sche.timersCount );
}

/**
 * @brief   Test Sched_registerTask function
 *      
 * The test verify that the scheduler can register 3 tasks succesfully 
 */
void test__Sched_registerTask_tasks( void )
{
    Sched_Scheduler_t    Sche;
    Sched_Task_t         tasks_array[ TASKS_N ];
    Sched_Timer_t        timers_array[ TIMERS_N ];

    Sched_initScheduler( &Sche, TASKS_N, TICK_VAL, SCHED_TIMEOUT, tasks_array, TIMERS_N, timers_array );

    uint8_t taskId = 0;
    taskId = Sched_registerTask(&Sche, Init_1, Task_1, TASKS_PERIOD);
    TEST_ASSERT_EQUAL_PTR( Init_1, Sche.taskPtr[taskId-1].initFunc );
    TEST_ASSERT_EQUAL_PTR( Task_1, Sche.taskPtr[taskId-1].taskFunc );
    TEST_ASSERT_EQUAL( 1, taskId );

    TEST_ASSERT_EQUAL( TASKS_PERIOD, Sche.taskPtr[taskId-1].period );
    taskId = Sched_registerTask(&Sche, Init_2, Task_2, TASKS_PERIOD);
    taskId = Sched_registerTask(&Sche, Init_3, Task_3, TASKS_PERIOD);
    TEST_ASSERT_EQUAL_PTR( Init_2, Sche.taskPtr[1].initFunc );
    TEST_ASSERT_EQUAL_PTR( Task_2, Sche.taskPtr[1].taskFunc );
    TEST_ASSERT_EQUAL_PTR( Init_3, Sche.taskPtr[2].initFunc );
    TEST_ASSERT_EQUAL_PTR( Task_3, Sche.taskPtr[2].taskFunc );
    TEST_ASSERT_EQUAL( 3, taskId );
    TEST_ASSERT_EQUAL( TASKS_PERIOD, Sche.taskPtr[1].period );
    TEST_ASSERT_EQUAL( TASKS_PERIOD, Sche.taskPtr[2].period );
    Sched_registerTask(&Sche, Init_3, Task_3, TASKS_PERIOD);
    TEST_ASSERT_EQUAL( 0, Sche.timersCount );
    TEST_ASSERT_EQUAL( 3, Sche.tasksCount );
}
/**
 * @brief   Test Sched_registerTask function
 *      
 * The test verify that the scheduler detects it cannot register more than the limit of tasks (3)
 */
void test__Sched_registerTask_limit( void )
{
    Sched_Scheduler_t    Sche;
    Sched_Task_t         tasks_array[ TASKS_N ];
    Sched_Timer_t        timers_array[ TIMERS_N ];

    Sched_initScheduler( &Sche, TASKS_N, TICK_VAL, SCHED_TIMEOUT, tasks_array, TIMERS_N, timers_array );

    Sched_registerTask(&Sche, Init_1, Task_1, TASKS_PERIOD);
    Sched_registerTask(&Sche, Init_2, Task_2, TASKS_PERIOD);
    Sched_registerTask(&Sche, Init_3, Task_3, TASKS_PERIOD);
    Sched_registerTask(&Sche, Init_4, Task_4, TASKS_PERIOD);
    TEST_ASSERT_EQUAL( 3, Sche.tasksCount );
}

/**
 * @brief   Test Sched_registerTask function
 *      
 * The test verify that the scheduler cannot register null tasks
 */
void test__Sched_registerTask_NULL( void )
{
    Sched_Scheduler_t    Sche;
    Sched_Task_t         tasks_array[ TASKS_N ];
    Sched_Timer_t        timers_array[ TIMERS_N ];

    Sched_initScheduler( &Sche, TASKS_N, TICK_VAL, SCHED_TIMEOUT, tasks_array, TIMERS_N, timers_array );
    Sched_registerTask(&Sche, NULL, NULL, TASKS_PERIOD);
    TEST_ASSERT_EQUAL( 0, Sche.tasksCount );
}

void Init_1(void){}
void Task_1(void){}
void Init_2(void){}
void Task_2(void){}
void Init_3(void){}
void Task_3(void){}
void Init_4(void){}
void Task_4(void){}