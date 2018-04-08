#include <Util/CircularBuffer.h>
#include "FormatOutputSpy.h"
#include <unity_fixture.h>


TEST_GROUP(CircularBufferPrint);

static CircularBuffer s_buffer;
static const char * s_expectedOutput;
static const char * s_actualOutput;

TEST_SETUP(CircularBufferPrint)
{
	UT_PTR_SET(formatOutput, formatOutputSpy);
	formatOutputSpy_create(100);
	s_actualOutput = formatOutputSpy_getOutput();
	s_buffer = CircularBuffer_create(10);
}

TEST_TEAR_DOWN(CircularBufferPrint)
{
	CircularBuffer_destroy(s_buffer);
	formatOutputSpy_destroy();
}

static void check()
{
	CircularBuffer_print(s_buffer);
	TEST_ASSERT_EQUAL_STRING(s_expectedOutput, s_actualOutput);
}

TEST(CircularBufferPrint, PrintEmpty)
{
	s_expectedOutput = "Circular buffer content:\n<>\n";
	check();
}

TEST(CircularBufferPrint, PrintAfterOneIsPut)
{
	CircularBuffer_put(s_buffer, 17);
	s_expectedOutput = "Circular buffer content:\n<17>\n";
	check();
}

TEST(CircularBufferPrint, PrintNotYetWrappedOrFull)
{
	CircularBuffer_put(s_buffer, 10);
	CircularBuffer_put(s_buffer, 20);
	CircularBuffer_put(s_buffer, 30);
	s_expectedOutput = "Circular buffer content:\n<10, 20, 30>\n";
	check();
}

TEST(CircularBufferPrint, PrintNotYetWrappedAndIsFull)
{
	CircularBuffer b = CircularBuffer_create(5);
	CircularBuffer_put(b, 31);
	CircularBuffer_put(b, 41);
	CircularBuffer_put(b, 59);
	CircularBuffer_put(b, 26);
	CircularBuffer_put(b, 53);
	s_expectedOutput = "Circular buffer content:\n<31, 41, 59, 26, 53>\n";
	CircularBuffer_print(b);
	STRCMP_EQUAL(s_expectedOutput, s_actualOutput);
	CircularBuffer_destroy(b);
}

TEST(CircularBufferPrint, PrintOldToNewWhenWrappedAndFull)
{
	CircularBuffer b = CircularBuffer_create(5);
	CircularBuffer_put(b, 200);
	CircularBuffer_put(b, 201);
	CircularBuffer_put(b, 202);
	CircularBuffer_put(b, 203);
	CircularBuffer_put(b, 204);
	LONGS_EQUAL(CircularBuffer_get(b), 200);
	CircularBuffer_put(b, 999);
	s_expectedOutput = "Circular buffer content:\n<201, 202, 203, 204, 999>\n";
	CircularBuffer_print(b);
	STRCMP_EQUAL(s_expectedOutput, s_actualOutput);
	CircularBuffer_destroy(b);
}


TEST_GROUP_RUNNER(CircularBufferPrint)
{
	RUN_TEST_CASE(CircularBufferPrint, PrintEmpty);
	RUN_TEST_CASE(CircularBufferPrint, PrintAfterOneIsPut);
	RUN_TEST_CASE(CircularBufferPrint, PrintNotYetWrappedOrFull);
	RUN_TEST_CASE(CircularBufferPrint, PrintNotYetWrappedAndIsFull);
	RUN_TEST_CASE(CircularBufferPrint, PrintOldToNewWhenWrappedAndFull);
}
