#include "unity.h"
#include "scheduler.h"

#define TRUE    1
#define FALSE   0

void setUp(void)
{
}

void tearDown(void)
{
}

/**
 * @brief   Test Sched_initScheduler function
 *
 * The test verify that the scheduler is initialized correctly using a queue of uint8_t types
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
    TEST_ASSERT_EQUAL( FALSE, hqueue.Full );
}