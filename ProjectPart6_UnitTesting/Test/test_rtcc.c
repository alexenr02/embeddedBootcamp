#include "unity.h"
#include "rtc.h"

#define TRUE    1
#define FALSE   0

void setUp(void)
{
}

void tearDown(void)
{
}

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
 * The test verify that the rtc getDate function works properly
 */
void test__Rtcc_getTime( void )
{
    Rtcc_Clock_t rtccClock;
    Rtcc_clockInit( &rtccClock );
    Rtcc_setTime( &rtccClock, 12, 30, 0 );
    Rtcc_setAlarm(&rtccClock, 12, 35);

    TEST_ASSERT_EQUAL( 12, rtccClock.al_hour );
    TEST_ASSERT_EQUAL( 35, rtccClock.al_min );
}