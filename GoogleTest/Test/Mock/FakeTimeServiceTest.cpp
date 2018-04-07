#include "FakeTimeService.h"
#include "gtest/gtest.h"

class FakeTimeServiceTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		TimeService_create();
	}

	virtual void TearDown()
	{
		TimeService_destroy();
	}
};

TEST_F(FakeTimeServiceTest, Create)
{
	Time time;
	TimeService_getTime(&time);
	EXPECT_EQ(TIME_UNKNOWN, time.minuteOfDay);
	EXPECT_EQ(TIME_UNKNOWN, time.dayOfWeek);
}

TEST_F(FakeTimeServiceTest, Set)
{
	Time time;
	FakeTimeService_setMinute(42);
	FakeTimeService_setDay(SATURDAY);
	TimeService_getTime(&time);
	EXPECT_EQ(42, time.minuteOfDay);
	EXPECT_EQ(SATURDAY, time.dayOfWeek);
}
