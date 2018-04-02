#include <unity_fixture.h>

static void RunAllTests(void)
{
	// RUN_TEST_GROUP(sprintf);
	RUN_TEST_GROUP(myfunc2x);
	RUN_TEST_GROUP(myfuncMemset);
	RUN_TEST_GROUP(LedDriver);
}

int main(int argc, const char * argv[])
{
	return UnityMain(argc, argv, RunAllTests);
}

// gcc AllTests.c MyFunc*.c ../lib/unity/*.c ../src/MyFunc.c -I../lib/unity -I../src/
