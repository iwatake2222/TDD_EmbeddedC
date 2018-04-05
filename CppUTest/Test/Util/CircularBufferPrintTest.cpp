#include <Util/CircularBuffer.h>
#include "FormatOutputSpy.h"
#include <CppUTest/TestHarness.h>

TEST_GROUP(CircularBufferPrint)
{
	CircularBuffer m_buffer;
	const char * m_expectedOutput;
	const char * m_actualOutput;

	void setup()
	{
		UT_PTR_SET(formatOutput, formatOutputSpy);
		formatOutputSpy_create(100);
		m_actualOutput = formatOutputSpy_getOutput();
		m_buffer = CircularBuffer_create(10);
	}

	void teardown()
	{
		CircularBuffer_destroy(m_buffer);
		formatOutputSpy_destroy();
	}

	void check()
	{
		CircularBuffer_print(m_buffer);
		STRCMP_EQUAL(m_expectedOutput, m_actualOutput);
	}
};

TEST(CircularBufferPrint, PrintEmpty)
{
	m_expectedOutput = "Circular buffer content:\n<>\n";
	check();
}

TEST(CircularBufferPrint, PrintAfterOneIsPut)
{
	CircularBuffer_put(m_buffer, 17);
	m_expectedOutput = "Circular buffer content:\n<17>\n";
	check();
}

TEST(CircularBufferPrint, PrintNotYetWrappedOrFull)
{
	CircularBuffer_put(m_buffer, 10);
	CircularBuffer_put(m_buffer, 20);
	CircularBuffer_put(m_buffer, 30);
	m_expectedOutput = "Circular buffer content:\n<10, 20, 30>\n";
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
	m_expectedOutput = "Circular buffer content:\n<31, 41, 59, 26, 53>\n";
	CircularBuffer_print(b);
	STRCMP_EQUAL(m_expectedOutput, m_actualOutput);
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
	m_expectedOutput = "Circular buffer content:\n<201, 202, 203, 204, 999>\n";
	CircularBuffer_print(b);
	STRCMP_EQUAL(m_expectedOutput, m_actualOutput);
	CircularBuffer_destroy(b);
}


