#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdint.h>

/********************************************************************************
 * Constant Definitions
 *******************************************************************************/


/********************************************************************************
 * Data Prototypes
 *******************************************************************************/

typedef struct _task {
    uint32_t        period;
    uint32_t        elapsed;
    uint8_t         startFlag;
    uint8_t         taskId;
    void            (*initFunc) (void);
    void            (*taskFunc) (void);
}Sched_Task_t;

typedef struct _AppSched_Timer {
    uint32_t        timeout;                /* Timer timeout to decrement and reload when the timer is re-started */
    uint32_t        count;                  /* Actual timer decrement count */
    uint8_t         startFlag;              /* Flag to start timer count */
    uint8_t         runFlag;
    void            (*callbackPtr)(void);   /* Pointer to callback function */
} Sched_Timer_t;

typedef struct {
    uint8_t         tasks;                  /* Number of tasks to handle */
    uint32_t        tick;                   /* Time base in ms */
    uint32_t        timeout;                /* Number of milliseconds the scheduler should run */
    uint8_t         tasksCount;             /* Internal task counter */
    Sched_Task_t    *taskPtr;               /* Pointer to buffer for the TCB tasks */
    uint8_t         timers;                 /* Number of software timer to use */
    Sched_Timer_t   *timerPtr;              /* Pointer to buffer timer array */
    uint8_t         timersCount;            /* Number of software timers registered */
} Sched_Scheduler_t;




/********************************************************************************
 * External Functions Prototypes
 *******************************************************************************/
/**
 * Function 
 * 
 * \param  
 * 
 * \return none
 */
void Sched_initScheduler ( Sched_Scheduler_t* scheduler, uint8_t tasks, uint32_t tick, uint32_t timeout, Sched_Task_t* taskPtr, uint8_t timers, Sched_Timer_t *timerPtr );

/**
 * Function 
 * 
 * \param  
 * \param      
 * 
 * \return  
 * 
 */
uint8_t Sched_registerTask( Sched_Scheduler_t* scheduler, void (*initPtr)(void), void(*taskPtr)(void), uint32_t period );

/**
 * Function
 * 
 * \param  
 * 
 * \return 
 * 
 */
uint8_t Sched_stopTask( Sched_Scheduler_t *scheduler, uint8_t task );

/**
 * Function 
 * 
 * \param 
 * 
 * \return 
 * 
 */


uint8_t Sched_startTask ( Sched_Scheduler_t *scheduler, uint8_t task );

/**
 * Function 
 * 
 * \param 
 *
 * \return 
 * 
 */
uint8_t Sched_periodicTask( Sched_Scheduler_t *scheduler, uint8_t task , uint32_t period );


/**
 * Function 
 * 
 * \param 
 * 
 * \return 
 * 
 */
uint8_t Sched_startScheduler( Sched_Scheduler_t *scheduler );

/**
 * Function 
 * 
 * \param 
 * 
 * \return 
 * 
 */
uint8_t Sched_registerTimer( Sched_Scheduler_t *scheduler, uint32_t timeout, void (*callbackPtr)(void) );

/**
 * Function 
 * 
 * \param 
 * 
 * \return 
 * 
 */
uint8_t Sched_getTimer( Sched_Scheduler_t *scheduler, uint8_t timer );

/**
 * Function 
 * 
 * \param 
 * 
 * \return 
 * 
 */
uint8_t Sched_reloadTimer( Sched_Scheduler_t *scheduler, uint8_t timer, uint32_t timeout );

/**
 * Function 
 * 
 * \param 
 * 
 * \return 
 * 
 */
uint8_t Sched_startTimer( Sched_Scheduler_t *scheduler, uint8_t timer );

/**
 * Function 
 * 
 * \param 
 * 
 * \return 
 * 
 */
uint8_t Sched_stopTimer( Sched_Scheduler_t *scheduler, uint8_t timer );

/**
 * Function 
 * 
 * \param none
 * 
 * \return none
 * 
 *
void test__AppBuffer_initBuffer__buffer_initialization( void );

/**
 * Function to test writting data into the buffer
 * 
 * \param none
 * 
 * \return none
 * 
 *

void test__AppBuffer_writeData__writting_a_single_data( void );

/**
 * Function to test filling all the buffer
 * 
 * \param none
 * 
 * \return none
 * 
 *

void test__AppBuffer_writeData__filling_the_buffer( void );
*/
#endif /* __SCHEDULER_H */