#include <Util/CircularBuffer.h>
#include "FormatOutputSpy.h"
#include "gtest/gtest.h"


class CircularBufferPrintTest : public ::testing::Test
{
protected:
	virtual void SetUp() {
		m_saved_formatOutput = formatOutput;
		formatOutput = formatOutputSpy;
		formatOutputSpy_create(100);
		m_actualOutput = formatOutputSpy_getOutput();
		m_buffer = CircularBuffer_create(10);
	}

	virtual void TearDown()
	{
		CircularBuffer_destroy(m_buffer);
		formatOutputSpy_destroy();
		formatOutput = m_saved_formatOutput;
	}

	void check()
	{
		CircularBuffer_print(m_buffer);
		EXPECT_STREQ(m_expectedOutput, m_actualOutput);
	}

	int (*m_saved_formatOutput)(const char* format, ...);

	CircularBuffer m_buffer;
	const char * m_expectedOutput;
	const char * m_actualOutput;
};

TEST_F(CircularBufferPrintTest, PrintEmpty)
{
	m_expectedOutput = "Circular buffer content:\n<>\n";
	check();
}

TEST_F(CircularBufferPrintTest, PrintAfterOneIsPut)
{
	CircularBuffer_put(m_buffer, 17);
	m_expectedOutput = "Circular buffer content:\n<17>\n";
	check();
}

TEST_F(CircularBufferPrintTest, PrintNotYetWrappedOrFull)
{
	CircularBuffer_put(m_buffer, 10);
	CircularBuffer_put(m_buffer, 20);
	CircularBuffer_put(m_buffer, 30);
	m_expectedOutput = "Circular buffer content:\n<10, 20, 30>\n";
	check();
}

TEST_F(CircularBufferPrintTest, PrintNotYetWrappedAndIsFull)
{
	CircularBuffer b = CircularBuffer_create(5);
	CircularBuffer_put(b, 31);
	CircularBuffer_put(b, 41);
	CircularBuffer_put(b, 59);
	CircularBuffer_put(b, 26);
	CircularBuffer_put(b, 53);
	m_expectedOutput = "Circular buffer content:\n<31, 41, 59, 26, 53>\n";
	CircularBuffer_print(b);
	EXPECT_STREQ(m_expectedOutput, m_actualOutput);
	CircularBuffer_destroy(b);
}

TEST_F(CircularBufferPrintTest, PrintOldToNewWhenWrappedAndFull)
{
	CircularBuffer b = CircularBuffer_create(5);
	CircularBuffer_put(b, 200);
	CircularBuffer_put(b, 201);
	CircularBuffer_put(b, 202);
	CircularBuffer_put(b, 203);
	CircularBuffer_put(b, 204);
	EXPECT_EQ(CircularBuffer_get(b), 200);
	CircularBuffer_put(b, 999);
	m_expectedOutput = "Circular buffer content:\n<201, 202, 203, 204, 999>\n";
	CircularBuffer_print(b);
	EXPECT_STREQ(m_expectedOutput, m_actualOutput);
	CircularBuffer_destroy(b);
}


