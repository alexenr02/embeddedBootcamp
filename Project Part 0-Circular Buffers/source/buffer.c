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
#include "buffer.h"
#include "common.h"

/********************************************************************************
 * Variable Declarations
 *******************************************************************************/

AppBuffer_Buffer testCircularBuffer;
unsigned char       testDato;
unsigned char       testData;
unsigned char       testArray[200];

/********************************************************************************
 * Private Function Prototypes
 *******************************************************************************/

/********************************************************************************
 * Public Function
 *******************************************************************************/

void AppBuffer_initBuffer( AppBuffer_Buffer* hbuffer) {
    hbuffer->Empty      = TRUE;
    hbuffer->Full       = FALSE;
    hbuffer->Head       = 0;
    hbuffer->Tail       = 0; 
}

void  AppBuffer_writeData( AppBuffer_Buffer* hbuffer, unsigned char data ) {
    // check if buffer is full
    if ( hbuffer->Full == TRUE ) {
        printf( "\n   Buffer is full! \n\n   " );      
    } else {
        hbuffer->Empty = FALSE;
        hbuffer->Buffer[hbuffer->Head] = data;
        hbuffer->Head++;
        
        if ( hbuffer->Head == hbuffer->Elements ) {
            hbuffer->Full = TRUE;
            hbuffer->Head = 0;
        }
    }    
}

unsigned char AppBuffer_readData( AppBuffer_Buffer* hbuffer ) {
    unsigned char readValue = hbuffer->Buffer[hbuffer->Tail];
    hbuffer->Buffer[hbuffer->Tail] = 0 ;
    hbuffer->Tail++;         //   Increase hbuffer->Head position to prepare for next read

    // if at last index in buffer, set readIndex back to 0
    if ( hbuffer->Tail == hbuffer->Elements ) {
        hbuffer->Empty = TRUE;
        hbuffer->Tail = 0;
    }   
    
    return readValue;
    
}

unsigned char AppBuffer_isBufferEmpty( AppBuffer_Buffer *hbuffer ) {
    if ( hbuffer->Empty == TRUE ) {
        printf( "\n    Buffer is empty!\n\n   " );
        return EMPTY;
    } 
    return NOT_EMPTY;

}

void test__AppBuffer_initBuffer__buffer_initialization( void ) {
    testCircularBuffer.Buffer = testArray;
    testCircularBuffer.Elements = 200u;
    AppBuffer_initBuffer( &testCircularBuffer );
    /* test cases */
    assert( testCircularBuffer.Head == 0 );
    assert( testCircularBuffer.Tail == 0 );
    assert( testCircularBuffer.Empty == 1 );
    assert( testCircularBuffer.Full == 0 );

    printf("\n    test buffer initialization succeed\n\n");
}

void test__AppBuffer_writeData__writting_a_single_data( void ) {
    testCircularBuffer.Buffer = testArray;
    testCircularBuffer.Elements = 3u;
    AppBuffer_initBuffer( &testCircularBuffer );
    AppBuffer_writeData( &testCircularBuffer, 0x23 );

    /* test cases */
    assert( testCircularBuffer.Head == 1 );
    assert( testCircularBuffer.Tail == 0 );
    assert( testArray[testCircularBuffer.Head-1] == 0x23 );
    assert( AppBuffer_isBufferEmpty( &testCircularBuffer ) == 0u );

    printf("\n    test writting a single data succeed\n\n");
}

void test__AppBuffer_writeData__filling_the_buffer( void ) {
    testCircularBuffer.Buffer = testArray;
    testCircularBuffer.Elements = 3u;
    AppBuffer_initBuffer( &testCircularBuffer );
    AppBuffer_writeData( &testCircularBuffer, 0x23 );
    AppBuffer_writeData( &testCircularBuffer, 0x23 );
    AppBuffer_writeData( &testCircularBuffer, 0x23 );
    
    /* test cases */
    assert( testCircularBuffer.Full == 1 );
    assert( testCircularBuffer.Head == 0 );

    printf("\n    test filling the buffer succeed\n\n");
}

//TODO test functions isbuffer empty and readData
/********************************************************************************
 * Private Function Definitions
 *******************************************************************************/



