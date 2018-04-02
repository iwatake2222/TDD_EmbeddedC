#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unity_fixture.h>
#include "MyFunc.h"

TEST_GROUP(myfuncMemset);

char output[100];
const char * expected;
#define MARKER 0xAA

TEST_SETUP(myfuncMemset)
{
	memset(output, MARKER, sizeof(output));
	expected = "";
}

TEST_TEAR_DOWN(myfuncMemset)
{
}

static void expect(const char *s)
{
	expected = s;
}

static void check(int writtenNum)
{
	TEST_ASSERT_EQUAL(strlen(expected), writtenNum);
	TEST_ASSERT_EQUAL_STRING(expected, output);
	TEST_ASSERT_BYTES_EQUAL(MARKER, output[writtenNum + 1]);
}

TEST(myfuncMemset, normal)
{
	expect("QQQQ");
	check(MyFunc_memset(output, 'Q', 4));
}

TEST_GROUP_RUNNER(myfuncMemset)
{
	RUN_TEST_CASE(myfuncMemset, normal);
}
