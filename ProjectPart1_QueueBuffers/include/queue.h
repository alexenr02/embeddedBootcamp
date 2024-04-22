#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdint.h>

/********************************************************************************
 * Constant Definitions
 *******************************************************************************/


/********************************************************************************
 * Data Prototypes
 *******************************************************************************/

/* a queue object 
*  contains all the information about the queue
*/
typedef struct {
    void            *Buffer;
    uint32_t        Elements;
    uint8_t         Size;
    uint8_t         Head;
    uint8_t         Tail;
    uint8_t         Empty;
    uint8_t         Full;
}Queue_Queue_t;




/********************************************************************************
 * External Functions Prototypes
 *******************************************************************************/
/**
 * Function 
 * 
 * \param queue  
 * 
 * \return none
 * 
 */
void Queue_initQueue( Queue_Queue_t* queue );

/**
 * Function 
 * 
 * \param queue   
 * \param data      
 * 
 * \return  
 * 
 */
uint8_t Queue_writeData( Queue_Queue_t* queue, void *data );

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
#endif /* __QUEUE_H */