#ifndef BUFFER_H_
#define BUFFER_H_

/********************************************************************************
 * Constant Definitions
 *******************************************************************************/


/********************************************************************************
 * Data Prototypes
 *******************************************************************************/

/* a buffer object 
*  contains all the information about the buffer
*/
typedef struct {
    unsigned char *Buffer;
    unsigned long Elements;
    unsigned long Head;
    unsigned long Tail;
    unsigned char Empty;
    unsigned char Full;
} AppBuffer_Buffer;


/********************************************************************************
 * External Functions Prototypes
 *******************************************************************************/
/**
 * Function to initialize the circular buffer by setting the head and tail elements
 * to zero, and the vlaues of empty to TRUE and full to FALSE
 * 
 * \param hbuffer pointer address of the buffer head 
 * 
 * \return none
 * 
 */
void AppBuffer_initBuffer( AppBuffer_Buffer* hbuffer );

/**
 * Function to write a new 8-bit data to the buffer if there is available
 * space. If there is no space, no data will be written. Function will 
 * determine if the queue is full with the last data written
 * 
 * \param hbuffer   pointer address of the buffer head
 * \param data      8-bit data that will be written on the buffer
 * 
 * \return none 
 * 
 */
void AppBuffer_writeData( AppBuffer_Buffer* hbuffer, unsigned char data );

/**
 * Function to read a data from the buffer, the data that is read will no longer
 * exists within the buffer. If the buffer is empty, no data will be read, and the value
 * returned by the function will not be valid. Function will determine if the queue
 * is empty with the last data read.
 * 
 * \param  hbuffer pointer address of the buffer head
 * 
 * \return value of the data read from the buffer
 * 
 */
unsigned char AppBuffer_readData( AppBuffer_Buffer* hbuffer );

/**
 * Function to determine if the buffer has no elements
 * 
 * \param  hbuffer pointer address of the buffer head
 * 
 * \return one if there are no more elements that can be read from the 
 * circular buffer and zero if there is at least one element that can be read. 
 * 
 */
unsigned char AppBuffer_isBufferEmpty( AppBuffer_Buffer *hbuffer );

/**
 * Function to test buffer initialization
 * 
 * \param none
 * 
 * \return none
 * 
 */
void test__AppBuffer_initBuffer__buffer_initialization( void );

/**
 * Function to test writting data into the buffer
 * 
 * \param none
 * 
 * \return none
 * 
 */

void test__AppBuffer_writeData__writting_a_single_data( void );

/**
 * Function to test filling all the buffer
 * 
 * \param none
 * 
 * \return none
 * 
 */

void test__AppBuffer_writeData__filling_the_buffer( void );

#endif /* __BUFFER_H */