#include "FakeTimeService.h"
#include <unity_fixture.h>

TEST_GROUP(FakeTimeService);

TEST_SETUP(FakeTimeService)
{
	TimeService_create();
}

TEST_TEAR_DOWN(FakeTimeService)
{
	TimeService_create();
}

TEST(FakeTimeService, Create)
{
	Time time;
	TimeService_getTime(&time);
	TEST_ASSERT_EQUAL(TIME_UNKNOWN, time.minuteOfDay);
	TEST_ASSERT_EQUAL(TIME_UNKNOWN, time.dayOfWeek);
}

TEST(FakeTimeService, Set)
{
	Time time;
	FakeTimeService_setMinute(42);
	FakeTimeService_setDay(SATURDAY);
	TimeService_getTime(&time);
	TEST_ASSERT_EQUAL(42, time.minuteOfDay);
	TEST_ASSERT_EQUAL(SATURDAY, time.dayOfWeek);
}

TEST_GROUP_RUNNER(FakeTimeService)
{
	RUN_TEST_CASE(FakeTimeService, Create);
	RUN_TEST_CASE(FakeTimeService, Set);
}


