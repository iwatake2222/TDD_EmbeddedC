#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unity_fixture.h>
#include "MyFunc.h"

TEST_GROUP(myfunc2x);

TEST_SETUP(myfunc2x)
{
}

TEST_TEAR_DOWN(myfunc2x)
{
}

TEST(myfunc2x, positive)
{
	TEST_ASSERT_EQUAL(4, MyFunc_2X(2));
}

TEST(myfunc2x, negative)
{
	TEST_ASSERT_EQUAL(-4, MyFunc_2X(-2));
}

TEST(myfunc2x, zero)
{
	TEST_ASSERT_EQUAL(0, MyFunc_2X(0));
}


TEST_GROUP_RUNNER(myfunc2x)
{
	RUN_TEST_CASE(myfunc2x, positive);
	RUN_TEST_CASE(myfunc2x, negative);
	RUN_TEST_CASE(myfunc2x, zero);
}
