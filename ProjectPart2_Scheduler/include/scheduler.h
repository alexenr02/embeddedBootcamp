#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdint.h>

/********************************************************************************
 * Constant Definitions
 *******************************************************************************/


/********************************************************************************
 * Data Prototypes
 *******************************************************************************/

typedef struct {
    uint8_t tasks;
    uint32_t tick;
    uint32_t timeout;
    uint8_t tasksCount;
    Sched_Task_t *taskPtr;
} Sched_Scheduler;

/* 
* 
*/
typedef struct {
    uint32_t period;
    uint32_t elapsed;
    uint8_t startFlag;
    void (*ïnitFunc) (void);
    void (*taskFunc) (void);

}Sched_Task_t;




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
void Sched_initScheduler ( Sched_Scheduler* scheduler  );

/**
 * Function 
 * 
 * \param  
 * \param      
 * 
 * \return  
 * 
 */
uint8_t Sched_registerTask( Sched_Scheduler* scheduler, void  );

/**
 * Function
 * 
 * \param  queue
 * 
 * \return 
 * 
 */
uint8_t Queue_readData( Queue_Queue_t* queue, void *data );

/**
 * Function 
 * 
 * \param queue
 * 
 * \return 
 * 
 */
uint8_t Queue_isQueueEmpty( Queue_Queue_t* queue );


/**
 * Function 
 * 
 * \param queue
 * 
 * \return 
 * 
 */
void Queue_flushQueue( Queue_Queue_t* queue );


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