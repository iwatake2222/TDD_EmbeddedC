#include <unity_fixture.h>

static void RunAllTests(void)
{
	// RUN_TEST_GROUP(sprintf);
	RUN_TEST_GROUP(myfunc2x);
	RUN_TEST_GROUP(myfuncMemset);
	RUN_TEST_GROUP(LedDriver);
	RUN_TEST_GROUP(FakeTimeService);
	RUN_TEST_GROUP(FormatOutputSpy);
	RUN_TEST_GROUP(LightControllerSpy);
	RUN_TEST_GROUP(CircularBufferPrint);
	RUN_TEST_GROUP(LightSchedulerRandomizeTest);
	RUN_TEST_GROUP(LightScheduler);
	RUN_TEST_GROUP(LightSchedulerInitAndCleanup);
	RUN_TEST_GROUP(RandomMinute);
	RUN_TEST_GROUP(Flash);
	RUN_TEST_GROUP(Flash_cmock);
}

int main(int argc, const char * argv[])
{
	return UnityMain(argc, argv, RunAllTests);
}

// gcc AllTests.c MyFunc*.c ../lib/unity/*.c ../src/MyFunc.c -I../lib/unity -I../src/
