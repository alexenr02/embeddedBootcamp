#include "unity.h"
#include "queue.h"

#define TRUE    1
#define FALSE   0

void setUp(void)
{
}

void tearDown(void)
{
}

//Declare the message to be handle by the queue
typedef struct {
    uint8_t msg;
    uint8_t value;
} MsgType_Message;

/**
 * @brief   Test Queue_Init function
 *
 * The test verify that the queue is initialized correctly using a queue of uint8_t types
 */
void test__Queue_initQueue__char_queue( void )
{
    Queue_Queue_t hqueue;
    uint8_t buffer[ 8 ];

    hqueue.Buffer   = buffer;
    hqueue.Elements = 8;
    hqueue.Size     = 1;
    Queue_initQueue( &hqueue );

    TEST_ASSERT_EQUAL_PTR( buffer, hqueue.Buffer );
    TEST_ASSERT_EQUAL( 8, hqueue.Elements );
    TEST_ASSERT_EQUAL( 1, hqueue.Size );
    TEST_ASSERT_EQUAL( 0, hqueue.Head );
    TEST_ASSERT_EQUAL( 0, hqueue.Tail );
    TEST_ASSERT_EQUAL( TRUE, hqueue.Empty );
    TEST_ASSERT_EQUAL_MESSAGE( FALSE, hqueue.Full, "Queue full flag failed");
}

/**
 * @brief   Test Queue_writeData function
 *
 * The test verify that data can be written correctly
 */
void test__Queue_writeData__MsgType_Message( void )
{
    
    MsgType_Message MsgToWrite;
    MsgType_Message MsgToRead;

    MsgType_Message buffer[ 6 ];
    Queue_Queue_t testQueue;

    testQueue.Buffer = (void*)buffer;
    testQueue.Elements = 6;
    testQueue.Size = sizeof( MsgType_Message );
    Queue_initQueue( &testQueue );
    
    MsgToWrite.msg = 2;
    MsgToWrite.value = 100u;
    Queue_writeData( &testQueue, &MsgToWrite );
    MsgToWrite.msg = 4;
    MsgToWrite.value = 200u;
    Queue_writeData( &testQueue, &MsgToWrite );


    TEST_ASSERT_EQUAL_PTR( buffer, testQueue.Buffer );
    TEST_ASSERT_EQUAL( 6, testQueue.Elements );
    TEST_ASSERT_EQUAL( 2, testQueue.Size );
    TEST_ASSERT_EQUAL( 0, testQueue.Head );
    TEST_ASSERT_EQUAL( 2, testQueue.Tail );
    TEST_ASSERT_EQUAL( FALSE, testQueue.Empty );
    TEST_ASSERT_EQUAL_MESSAGE( FALSE, testQueue.Full, "Queue full flag failed");
}

/**
 * @brief   Test Queue_writeData function
 *
 * The test verify that queue can be fulled completely
 */
void test__Queue_writeData__full( void )
{
    
    MsgType_Message MsgToWrite;
    MsgType_Message MsgToRead;

    MsgType_Message buffer[ 3 ];
    Queue_Queue_t testQueue;

    testQueue.Buffer = (void*)buffer;
    testQueue.Elements = 3;
    testQueue.Size = sizeof( MsgType_Message );
    Queue_initQueue( &testQueue );
    
    MsgToWrite.msg = 2;
    MsgToWrite.value = 100u;
    Queue_writeData( &testQueue, &MsgToWrite );
    MsgToWrite.msg = 4;
    MsgToWrite.value = 200u;
    Queue_writeData( &testQueue, &MsgToWrite );
    MsgToWrite.msg = 6;
    MsgToWrite.value = 240u;
    Queue_writeData( &testQueue, &MsgToWrite );
    MsgToWrite.msg = 7;
    MsgToWrite.value = 250u;

    Queue_writeData( &testQueue, &MsgToWrite );
    TEST_ASSERT_EQUAL_PTR( buffer, testQueue.Buffer );
    TEST_ASSERT_EQUAL( 3, testQueue.Elements );
    TEST_ASSERT_EQUAL( 2, testQueue.Size );
    TEST_ASSERT_EQUAL( 0, testQueue.Head );
    TEST_ASSERT_EQUAL( 0, testQueue.Tail );
    TEST_ASSERT_EQUAL( FALSE, testQueue.Empty );
    TEST_ASSERT_EQUAL_MESSAGE( TRUE, testQueue.Full, "Queue full flag failed");
}

/**
 * @brief   Test Queue_readData function
 *
 * The test verify that queue can be read completely
 */
void test__Queue_readData__MsgType_Message( void )
{
    
    MsgType_Message MsgToWrite;
    MsgType_Message MsgToRead;

    MsgType_Message buffer[ 3 ];
    Queue_Queue_t testQueue;

    testQueue.Buffer = (void*)buffer;
    testQueue.Elements = 3;
    testQueue.Size = sizeof( MsgType_Message );
    Queue_initQueue( &testQueue );
    
    MsgToWrite.msg = 2;
    MsgToWrite.value = 100u;
    Queue_writeData( &testQueue, &MsgToWrite );
    MsgToWrite.msg = 4;
    MsgToWrite.value = 200u;
    Queue_writeData( &testQueue, &MsgToWrite );
    MsgToWrite.msg = 6;
    MsgToWrite.value = 240u;
    Queue_writeData( &testQueue, &MsgToWrite );


    Queue_readData( &testQueue, &MsgToRead );
    TEST_ASSERT_EQUAL( 2, MsgToRead.msg );
    TEST_ASSERT_EQUAL( 100u, MsgToRead.value );

    Queue_readData( &testQueue, &MsgToRead );
    TEST_ASSERT_EQUAL( 4, MsgToRead.msg );
    TEST_ASSERT_EQUAL( 200, MsgToRead.value );

    Queue_readData( &testQueue, &MsgToRead );
    TEST_ASSERT_EQUAL( 6, MsgToRead.msg );
    TEST_ASSERT_EQUAL( 240, MsgToRead.value );

    Queue_readData( &testQueue, &MsgToRead );
    TEST_ASSERT_EQUAL( 0, testQueue.Head );
    TEST_ASSERT_EQUAL( 0, testQueue.Tail );
    TEST_ASSERT_EQUAL( TRUE, testQueue.Empty );

}

/**
 * @brief   Test Queue_readData function
 *
 * The test verify that queue can be read completely
 */
void test__Queue_isQueueEmpty__MsgType_Message( void )
{
    
    MsgType_Message MsgToWrite;
    MsgType_Message MsgToRead;

    MsgType_Message buffer[ 2 ];
    Queue_Queue_t testQueue;

    testQueue.Buffer = (void*)buffer;
    testQueue.Elements = 2;
    testQueue.Size = sizeof( MsgType_Message );
    Queue_initQueue( &testQueue );
    
    MsgToWrite.msg = 2;
    MsgToWrite.value = 100u;
    Queue_writeData( &testQueue, &MsgToWrite );
    MsgToWrite.msg = 4;
    MsgToWrite.value = 200u;
    Queue_writeData( &testQueue, &MsgToWrite );

    Queue_readData( &testQueue, &MsgToRead );
    Queue_readData( &testQueue, &MsgToRead );
    
    uint8_t result = Queue_isQueueEmpty(&testQueue);
    TEST_ASSERT_EQUAL( 1, result );
}

/**
 * @brief   Test Queue_flushQueue function
 *
 * The test verify that queue can be flushed succesfully
 */
void test__Queue_flushQueue__MsgType_Message( void )
{
    
    MsgType_Message MsgToWrite;
    MsgType_Message MsgToRead;

    MsgType_Message buffer[ 2 ];
    Queue_Queue_t testQueue;

    testQueue.Buffer = (void*)buffer;
    testQueue.Elements = 2;
    testQueue.Size = sizeof( MsgType_Message );
    Queue_initQueue( &testQueue );
    
    MsgToWrite.msg = 2;
    MsgToWrite.value = 100u;
    Queue_writeData( &testQueue, &MsgToWrite );
    MsgToWrite.msg = 4;
    MsgToWrite.value = 200u;
    Queue_writeData( &testQueue, &MsgToWrite );
    uint8_t readResult = Queue_readData( &testQueue, &MsgToRead );
    Queue_flushQueue(&testQueue);
    
    uint8_t result = Queue_isQueueEmpty(&testQueue);
    TEST_ASSERT_EQUAL( 1, readResult );
    TEST_ASSERT_EQUAL( 1, result );
    TEST_ASSERT_EQUAL( 1, testQueue.Empty );
    TEST_ASSERT_EQUAL( 0, testQueue.Head );
    TEST_ASSERT_EQUAL( 0, testQueue.Tail );
    TEST_ASSERT_EQUAL_PTR( NULL, testQueue.Buffer );
}