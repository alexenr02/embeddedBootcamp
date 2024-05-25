#include "unity.h"
#include "dummy.h"

void setUp(void)
{
}

void tearDown(void)
{
}


void test__substraction__two_integers(void)
{
    /*We give an initial value to our global variable, ceedling nows about
    the variable because the external reference in dummy.h*/
    subs = 10;
    /*call function under test that make use of global function*/
    uint32_t res = substraction( 20 );
    TEST_ASSERT_EQUAL_MESSAGE( 10, res, "20 - 10 = 10" );
}