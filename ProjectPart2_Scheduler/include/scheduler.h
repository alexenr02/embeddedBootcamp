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
    uint32_t period;
    uint32_t elapsed;
    uint8_t startFlag;
    void (*initFunc) (void);
    void (*taskFunc) (void);
}Sched_Task_t;

typedef struct {
    uint8_t tasks;
    uint32_t tick;
    uint32_t timeout;
    uint8_t tasksCount;
    Sched_Task_t *taskPtr;
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
 * 
 */
void Sched_initScheduler ( Sched_Scheduler_t* scheduler  );

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


//uint8_t Sched_startTask ( Sched_Scheduler_t *scheduler, uint8_t task );

/**
 * Function 
 * 
 * \param 
 *
 * \return 
 * 
 */
//uint8_t Sched_periodicTask( Sched_Scheduler_t *scheduler, uint32_t period );


/**
 * Function 
 * 
 * \param 
 * 
 * \return 
 * 
 */
//uint8_t Sched_startScheduler( Sched_Scheduler_t *scheduler );

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