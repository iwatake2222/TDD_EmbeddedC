#include <stdio.h>

#include "CppUTest/CommandLineTestRunner.h"

TEST_GROUP(FirstTestGroup)
{
};

TEST(FirstTestGroup, FirstTest)
{
	// FAIL("Fail me!");
}


int main(int argc, const char * argv[])
{
	printf("This is test code.\n");

	return RUN_ALL_TESTS(argc, argv);
}
