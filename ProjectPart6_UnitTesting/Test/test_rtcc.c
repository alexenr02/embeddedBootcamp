#include "unity.h"
#include "rtc.h"
#include "common.h"

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
 * @brief   Test Rtcc_clockInit function
 *      
 * The test verify that the rtc init function works properly
 */
void test__Rtcc_clockInit( void )
{
    Rtcc_Clock_t rtccClock;
    Rtcc_clockInit( &rtccClock );
    
    TEST_ASSERT_EQUAL( 0, rtccClock.tm_sec );
    TEST_ASSERT_EQUAL( 0, rtccClock.tm_min );
    TEST_ASSERT_EQUAL( 0, rtccClock.tm_hour );
    TEST_ASSERT_EQUAL( 1, rtccClock.tm_day );
    TEST_ASSERT_EQUAL( 1, rtccClock.tm_mon );
    TEST_ASSERT_EQUAL( 1900, rtccClock.tm_year );
    TEST_ASSERT_EQUAL( 0, rtccClock.tm_wday );
    TEST_ASSERT_EQUAL( 0, rtccClock.al_min );
    TEST_ASSERT_EQUAL( 0, rtccClock.al_hour ); 
}



/**
 * @brief   Test Rtcc_setTime function
 *      
 * The test verify that the rtc setTime function works properly
 */
void test__Rtcc_setTime( void )
{
    Rtcc_Clock_t rtccClock;
    Rtcc_clockInit( &rtccClock );
    Rtcc_setTime( &rtccClock, 12, 30, 0 );

    TEST_ASSERT_EQUAL( 0, rtccClock.tm_sec );
    TEST_ASSERT_EQUAL( 30, rtccClock.tm_min );
    TEST_ASSERT_EQUAL( 12, rtccClock.tm_hour );
}

/**
 * @brief   Test Rtcc_setDate function
 *      
 * The test verify that the rtc setDate function works properly
 */
void test__Rtcc_setDate( void )
{
    Rtcc_Clock_t rtccClock;
    Rtcc_clockInit( &rtccClock );

    Rtcc_setDate( &rtccClock, 18, 5, 2024 );

    TEST_ASSERT_EQUAL( 18, rtccClock.tm_day );
    TEST_ASSERT_EQUAL( 5, rtccClock.tm_mon );
    TEST_ASSERT_EQUAL( 2024, rtccClock.tm_year );
    TEST_ASSERT_EQUAL( Saturday, rtccClock.tm_wday ); 
    Rtcc_setDate( &rtccClock, 19, 5, 2024 );
    TEST_ASSERT_EQUAL( Sunday, rtccClock.tm_wday ); 
    Rtcc_setDate( &rtccClock, 20, 5, 2024 );
    TEST_ASSERT_EQUAL( Monday, rtccClock.tm_wday ); 
    Rtcc_setDate( &rtccClock, 21, 5, 2024 );
    TEST_ASSERT_EQUAL( Tuesday, rtccClock.tm_wday ); 
    Rtcc_setDate( &rtccClock, 22, 5, 2024 );
    TEST_ASSERT_EQUAL( Wednesday, rtccClock.tm_wday ); 
    Rtcc_setDate( &rtccClock, 23, 5, 2024 );
    TEST_ASSERT_EQUAL( Thursday, rtccClock.tm_wday ); 
    Rtcc_setDate( &rtccClock, 41, 5, 2500 );
    TEST_ASSERT_EQUAL( 2024, rtccClock.tm_year ); 
    TEST_ASSERT_EQUAL( 23, rtccClock.tm_day ); 
}

/**
 * @brief   Test Rtcc_setAlarm function
 *      
 * The test verify that the rtc setAlarm function works properly
 */
void test__Rtcc_setAlarm( void )
{
    Rtcc_Clock_t rtccClock;
    Rtcc_clockInit( &rtccClock );
    Rtcc_setTime( &rtccClock, 12, 30, 0 );
    Rtcc_setAlarm(&rtccClock, 12, 35);

    TEST_ASSERT_EQUAL( 12, rtccClock.al_hour );
    TEST_ASSERT_EQUAL( 35, rtccClock.al_min );
}

/**
 * @brief   Test Rtcc_getTime function
 *      
 * The test verify that the rtc getTime function works properly
 */
void test__Rtcc_getTime( void )
{
    Message msgToWrite;
    
    Rtcc_Clock_t rtccClock;
    Rtcc_clockInit( &rtccClock );
    Rtcc_setTime( &rtccClock, 12, 30, 0 );
    /*get time and date and send time and date to 500ms task using a queue */
    Rtcc_getTime( &rtccClock, &msgToWrite.hour, &msgToWrite.minutes, &msgToWrite.seconds, &msgToWrite.msg );

    TEST_ASSERT_EQUAL( 12, rtccClock.tm_hour );
    TEST_ASSERT_EQUAL( 30, rtccClock.tm_min );
    TEST_ASSERT_EQUAL( 0, rtccClock.tm_sec );
}

/**
 * @brief   Test Rtcc_getDate function
 *      
 * The test verify that the rtc getDate function works properly
 */
void test__Rtcc_getDate( void )
{
    Message msgToWrite;
    
    Rtcc_Clock_t rtccClock;
    Rtcc_clockInit( &rtccClock );
    Rtcc_setDate( &rtccClock, 18, 5, 2024 );

    /*get time and date and send time and date to 500ms task using a queue */
    Rtcc_getDate( &rtccClock, &msgToWrite.day, &msgToWrite.month, &msgToWrite.year, &msgToWrite.wday, &msgToWrite.msg );
    TEST_ASSERT_EQUAL( 18, rtccClock.tm_day );
    TEST_ASSERT_EQUAL( 5, rtccClock.tm_mon );
    TEST_ASSERT_EQUAL( 2024, rtccClock.tm_year );
}

/**
 * @brief   Test Rtcc_getAlarm function
 *      
 * The test verify that the rtc Rtcc_getAlarm function works properly
 */
void test__Rtcc_getAlarm( void )
{
    Rtcc_Clock_t rtccClock;
    Rtcc_clockInit( &rtccClock );
    Rtcc_setAlarm( &rtccClock, 20, 5 );
    uint8_t hour = 0;
    uint8_t minutes = 0;

    /*get time and date and send time and date to 500ms task using a queue */
    Rtcc_getAlarm( &rtccClock, &hour,  &minutes);
    TEST_ASSERT_EQUAL( 20, hour );
    TEST_ASSERT_EQUAL( 5, minutes );
}

/**
 * @brief   Test Rtcc_periodicTask function
 *      
 * The test verify that the rtc Rtcc_periodicTask function works properly
 */
void test__Rtcc_periodicTask( void )
{
    Rtcc_Clock_t  rtccClock;
    Rtcc_clockInit( &rtccClock );
    Rtcc_setTime( &rtccClock, 23, 59, 58 );
    Rtcc_setDate( &rtccClock, 31, 12, 2023 );
    Rtcc_periodicTask(&rtccClock);
    Rtcc_periodicTask(&rtccClock);
    Rtcc_periodicTask(&rtccClock);
    Rtcc_periodicTask(&rtccClock);
    Rtcc_periodicTask(&rtccClock);
    TEST_ASSERT_EQUAL( 00, rtccClock.tm_hour );
    TEST_ASSERT_EQUAL( 00, rtccClock.tm_min );
    TEST_ASSERT_EQUAL( 3, rtccClock.tm_sec );

    Rtcc_setTime( &rtccClock, 23, 59, 58 );
    Rtcc_setDate( &rtccClock, 28, 2, 2024 );
    Rtcc_periodicTask(&rtccClock);
    Rtcc_periodicTask(&rtccClock);
    Rtcc_periodicTask(&rtccClock);
    Rtcc_periodicTask(&rtccClock);
    Rtcc_periodicTask(&rtccClock);
    TEST_ASSERT_EQUAL( 00, rtccClock.tm_hour );
    TEST_ASSERT_EQUAL( 00, rtccClock.tm_min );
    TEST_ASSERT_EQUAL( 3, rtccClock.tm_sec );
    TEST_ASSERT_EQUAL( 29, rtccClock.tm_day );
    TEST_ASSERT_EQUAL( 2, rtccClock.tm_mon );
    TEST_ASSERT_EQUAL( 2024, rtccClock.tm_year );
}