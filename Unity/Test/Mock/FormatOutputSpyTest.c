#include "FormatOutputSpy.h"
#include <unity_fixture.h>

TEST_GROUP(FormatOutputSpy);

TEST_SETUP(FormatOutputSpy)
{
	UT_PTR_SET(formatOutput, formatOutputSpy);
}

TEST_TEAR_DOWN(FormatOutputSpy)
{
	formatOutputSpy_destroy();
}

TEST(FormatOutputSpy, HelloWorld)
{
	formatOutputSpy_create(20);
	formatOutput("Hello, World\n");
	STRCMP_EQUAL("Hello, World\n", formatOutputSpy_getOutput());
}

TEST(FormatOutputSpy, LimitTheOutputBufferSize)
{
	formatOutputSpy_create(4);
	formatOutput("Hello, World\n");
	STRCMP_EQUAL("Hell", formatOutputSpy_getOutput());
}


TEST(FormatOutputSpy, PrintMultipleTimes)
{
	formatOutputSpy_create(25);
	formatOutput("Hello");
	formatOutput(", World\n");
	STRCMP_EQUAL("Hello, World\n", formatOutputSpy_getOutput());
}

TEST(FormatOutputSpy, PrintMultipleOutputsPastFull)
{
	formatOutputSpy_create(12);
	formatOutput("12345");
	formatOutput("67890");
	formatOutput("ABCDEF");
	STRCMP_EQUAL("1234567890AB", formatOutputSpy_getOutput());
}

TEST_GROUP_RUNNER(FormatOutputSpy)
{
	RUN_TEST_CASE(FormatOutputSpy, HelloWorld);
	RUN_TEST_CASE(FormatOutputSpy, LimitTheOutputBufferSize);
	RUN_TEST_CASE(FormatOutputSpy, PrintMultipleTimes);
	RUN_TEST_CASE(FormatOutputSpy, PrintMultipleOutputsPastFull);
}
