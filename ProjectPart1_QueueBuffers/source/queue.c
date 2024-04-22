/**
 * \file buffer.c
 * 
 * Functions call necessary for the circular buffer. The circular buffer will
 * store a specific amount of values and it is operated by a FIFO logic.
 * 
*/

/********************************************************************************
 * Header Files
 *******************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "queue.h"
#include "common.h"

/********************************************************************************
 * Variable Declarations
 *******************************************************************************/

/********************************************************************************
 * Private Function Prototypes
 *******************************************************************************/

/********************************************************************************
 * Public Function
 *******************************************************************************/

void Queue_initQueue( Queue_Queue* queue ) {
    queue->Empty      = TRUE;
    queue->Full       = FALSE;
    queue->Head       = 0;
    queue->Tail       = 0; 
}

uint8_t Queue_writeData( Queue_Queue* queue, void *data ) {
    // check if queue is full
    if ( queue->Full == TRUE ) {
        printf( "\n   Queue is full! \n\n   " );
        return FALSE;      
    } else {
        queue->Empty = FALSE;
        memcpy(queue->Buffer, data, sizeof((queue->Size)*queue->Elements));
        queue->Head++;
        
        if ( queue->Head == queue->Elements ) {
            queue->Full = TRUE;
            queue->Head = 0;
        }
        return TRUE;
    }           
}

uint8_t Queue_readData( Queue_Queue* queue, void* data ) {
    memcpy(data, queue->Buffer, sizeof((queue->Size)*queue->Elements));
    queue->Tail++;         //   Increase hbuffer->Head position to prepare for next read  
}

uint8_t Queue_isQueueEmpty( Queue_Queue* queue ) {

}


//TODO test functions isbuffer empty and readData
/********************************************************************************
 * Private Function Definitions
 *******************************************************************************/



