#include "FakeTimeService.h"
#include <CppUTest/TestHarness.h>

TEST_GROUP(FakeTimeService)
{
	void setup()
	{
		TimeService_create();
	}

	void teardown()
	{
		TimeService_destroy();
	}
};

TEST(FakeTimeService, Create)
{
	Time time;
	TimeService_getTime(&time);
	LONGS_EQUAL(TIME_UNKNOWN, time.minuteOfDay);
	LONGS_EQUAL(TIME_UNKNOWN, time.dayOfWeek);
}

TEST(FakeTimeService, Set)
{
	Time time;
	FakeTimeService_setMinute(42);
	FakeTimeService_setDay(SATURDAY);
	TimeService_getTime(&time);
	LONGS_EQUAL(42, time.minuteOfDay);
	LONGS_EQUAL(SATURDAY, time.dayOfWeek);
}
