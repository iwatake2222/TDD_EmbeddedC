#include "FormatOutputSpy.h"
#include "gtest/gtest.h"

class FormatOutputSpyTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		m_saved_formatOutput = formatOutput;
		formatOutput = formatOutputSpy;
	}
	
	virtual void TearDown()
	{
		formatOutputSpy_destroy();
		formatOutput = m_saved_formatOutput;
	}

	int (*m_saved_formatOutput)(const char* format, ...);
};


TEST_F(FormatOutputSpyTest, HelloWorld)
{
	formatOutputSpy_create(20);
	formatOutput("Hello, World\n");
	EXPECT_STREQ("Hello, World\n", formatOutputSpy_getOutput());
}

TEST_F(FormatOutputSpyTest, LimitTheOutputBufferSize)
{
	formatOutputSpy_create(4);
	formatOutput("Hello, World\n");
	EXPECT_STREQ("Hell", formatOutputSpy_getOutput());
}


TEST_F(FormatOutputSpyTest, PrintMultipleTimes)
{
	formatOutputSpy_create(25);
	formatOutput("Hello");
	formatOutput(", World\n");
	EXPECT_STREQ("Hello, World\n", formatOutputSpy_getOutput());
}

TEST_F(FormatOutputSpyTest, PrintMultipleOutputsPastFull)
{
	formatOutputSpy_create(12);
	formatOutput("12345");
	formatOutput("67890");
	formatOutput("ABCDEF");
	EXPECT_STREQ("1234567890AB", formatOutputSpy_getOutput());
}

