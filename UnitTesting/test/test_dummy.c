#include "unity.h"
#include "dummy.h"

void setUp(void)
{
}

void tearDown(void)
{
}

/*test case 1: for function sum*/
void test__sum__2_plus_3_equal_5(void)
{
    uint32_t res = sum( 2, 3 );
    TEST_ASSERT_EQUAL_MESSAGE( 5, res, "2 + 3 = 5" );
}

/*test case 2: for function sum*/
void test__sum__100_plus_50_equal_150(void)
{
    uint32_t res = sum( 100, 50 );
    TEST_ASSERT_EQUAL_MESSAGE( 150, res, "100 + 50 = 150" );
}

/*test case 1: for function sub*/
void test__sub__100_minus_50_equal_50(void)
{
    uint32_t res = sub( 100, 50 );
    TEST_ASSERT_EQUAL_MESSAGE( 50, res, "100 - 50 = 50" );
}

/*test case 2: for function sub*/
void test__sub__3_minus_2_equal_minus_1(void)
{
    uint32_t res = sub( 3, 2 );
    TEST_ASSERT_EQUAL_MESSAGE( 1, res, "3 - 2 = 1" );
}

/*test case 1: for function mul*/
void test__mul__2_by_3_equal_6(void)
{
    uint32_t res = mul( 2, 3 );
    TEST_ASSERT_EQUAL_MESSAGE( 6, res, "2 * 3 = 6" );
}

/*test case 2: for function mul*/
void test__mul__100_by_50_equal_5000(void)
{
    uint32_t res = mul( 100, 50 );
    TEST_ASSERT_EQUAL_MESSAGE( 5000, res, "100 * 50 = 5000" );
}

void test__sum__error_result(void)
{
    uint32_t res = sum( 2, 3 );
    TEST_ASSERT_EQUAL_MESSAGE( 6, res, "2 + 3 = 6" );
}

void test__increment__one_integer(void)
{
    uint32_t res = increment( 2 );
    TEST_ASSERT_EQUAL_MESSAGE( 3, res, "2++ = 3" );
}