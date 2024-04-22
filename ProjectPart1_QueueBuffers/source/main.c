#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "queue.h"
#include "userInterface.h"
#include "common.h"

#define ELEMENTS 10

//Declare the message to be handle by the queue
typedef struct {
    uint8_t msg;
    uint8_t value;
} MsgType_Message;

int main( void )
{
    MsgType_Message MsgToWrite;
    MsgType_Message MsgToRead;

    MsgType_Message buffer[ ELEMENTS ];
    Queue_Queue Queue;

    Queue.Buffer = (void*)buffer;
    Queue.Elements = ELEMENTS;
    Queue.Size = sizeof( MsgType_Message );
    Queue_initQueue( &Queue );
    
    MsgToWrite.msg = 2;
    MsgToWrite.value = 100u;
    Queue_writeData( &Queue, &MsgToWrite );

    while(Queue_isQueueEmpty( &Queue, &MsgToRead )) {
        Queue_readData(&Queue, &MsgToRead);
        printf( "\n\nmsg read from the queue %d\n ", MsgToRead.msg);
        printf( "\n\nvalue read from the queue %d\n ", MsgToRead.value );
    }
    
    return 0;
}