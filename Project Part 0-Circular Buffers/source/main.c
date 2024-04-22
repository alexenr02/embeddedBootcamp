#include <stdio.h>
#include <stdint.h>
#include "buffer.h"
#include "userInterface.h"
#include "common.h"

int main( void )
{
    unsigned char       dato;
    unsigned char       data;
    unsigned char       array[200];
    AppBuffer_Buffer    circularBuffer;                         

    circularBuffer.Buffer               = array;
    circularBuffer.Elements             = 2u;

    AppBuffer_initBuffer( &circularBuffer );
    
    dato = 100;
    AppBuffer_writeData( &circularBuffer, dato );

    dato = 120;
    AppBuffer_writeData( &circularBuffer, dato );

    dato = 200;
    AppBuffer_writeData( &circularBuffer, dato );

    // read all the messages
    while ( AppBuffer_isBufferEmpty( &circularBuffer ) == NOT_EMPTY ) {
        data = AppBuffer_readData ( &circularBuffer );
        printf("\n    Data read from the queue %d\n", data);
    }

    printf("\n\n\n");

    test__AppBuffer_initBuffer__buffer_initialization();
    test__AppBuffer_writeData__writting_a_single_data();
    test__AppBuffer_writeData__filling_the_buffer();
    return 0;
}