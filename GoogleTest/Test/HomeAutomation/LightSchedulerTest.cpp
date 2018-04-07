#include "../Mock/LightControllerSpy.h"
#include "../Mock/FakeTimeService.h"
#include <HomeAutomation/LightScheduler.h>
#include "gtest/gtest.h"

class LightSchedulerTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		TimeService_create();
		LightController_create();
		LightScheduler_create();
	}
	
	virtual void TearDown()
	{
		TimeService_destroy();
		LightController_destroy();
		LightScheduler_destroy();
	}

	void setTimeTo(int day, int minuteOfDay)
	{
		FakeTimeService_setDay(day);
		FakeTimeService_setMinute(minuteOfDay);
	}

	void checkLightState(int id, int level)
	{
		// EXPECT_EQ(id, LightControllerSpy_getLastId());
		// EXPECT_EQ(level, LightControllerSpy_getLastState());
		EXPECT_EQ(level, LightControllerSpy_getLightState(id));
	}
};



TEST_F(LightSchedulerTest, NoChangeToLightsDuringInitialization)
{
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST_F(LightSchedulerTest, NoSchedulerNothingHappens)
{
	setTimeTo(MONDAY, 100);
	LightScheduler_wakeup();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}


TEST_F(LightSchedulerTest, ScheduleOnEverydayNotTimeYet)
{
	LightScheduler_scheduleTurnOn(3, EVERYDAY, 1200);
	setTimeTo(MONDAY, 1199);
	LightScheduler_wakeup();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST_F(LightSchedulerTest, ScheduleOnEverydayItsTime)
{
	LightScheduler_scheduleTurnOn(3, EVERYDAY, 1200);
	setTimeTo(MONDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(3, LIGHT_STATE_ON);
}

TEST_F(LightSchedulerTest, ScheduleOffEverydayItsTime)
{
	LightScheduler_scheduleTurnOff(3, EVERYDAY, 1200);
	setTimeTo(MONDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(3, LIGHT_STATE_OFF);
}

TEST_F(LightSchedulerTest, ScheduleTuesdayButItsMonday)
{
	LightScheduler_scheduleTurnOff(3, TUESDAY, 1200);
	setTimeTo(MONDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST_F(LightSchedulerTest, ScheduleTuesdayAndItsTuesday)
{
	LightScheduler_scheduleTurnOn(3, TUESDAY, 1200);
	setTimeTo(TUESDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(3, LIGHT_STATE_ON);
}

TEST_F(LightSchedulerTest, ScheduleWeekEndItsFriday)
{
	LightScheduler_scheduleTurnOn(3, WEEKEND, 1200);
	setTimeTo(FRIDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST_F(LightSchedulerTest, ScheduleWeekEndItsSaturday)
{
	LightScheduler_scheduleTurnOn(3, WEEKEND, 1200);
	setTimeTo(SATURDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(3, LIGHT_STATE_ON);
}

TEST_F(LightSchedulerTest, ScheduleWeekEndItsSunday)
{
	LightScheduler_scheduleTurnOn(3, WEEKEND, 1200);
	setTimeTo(SUNDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(3, LIGHT_STATE_ON);
}

TEST_F(LightSchedulerTest, ScheduleWeekEndItsMonday)
{
	LightScheduler_scheduleTurnOn(3, WEEKEND, 1200);
	setTimeTo(MONDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST_F(LightSchedulerTest, ScheduleWeekDayItsSunday)
{
	LightScheduler_scheduleTurnOn(3, WEEKDAY, 1200);
	setTimeTo(SUNDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST_F(LightSchedulerTest, ScheduleWeekDayItsSaturday)
{
	LightScheduler_scheduleTurnOn(3, WEEKDAY, 1200);
	setTimeTo(SATURDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST_F(LightSchedulerTest, ScheduleWeekDayItsMonday)
{
	LightScheduler_scheduleTurnOn(3, WEEKDAY, 1200);
	setTimeTo(MONDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(3, LIGHT_STATE_ON);
}

TEST_F(LightSchedulerTest, ScheduleWeekDayItsFriday)
{
	LightScheduler_scheduleTurnOn(3, WEEKDAY, 1200);
	setTimeTo(FRIDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(3, LIGHT_STATE_ON);
}

TEST_F(LightSchedulerTest, ScheduleTwoEventsAtTheSameTime)
{
	LightScheduler_scheduleTurnOn(3, SUNDAY, 1200);
	LightScheduler_scheduleTurnOff(12, SUNDAY, 1200);
	setTimeTo(SUNDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(3, LIGHT_STATE_ON);
	checkLightState(12, LIGHT_STATE_OFF);
}

TEST_F(LightSchedulerTest, RejectTooManyEvents)
{
	int i;
	for (i = 0; i < 128; i++) {
		EXPECT_EQ(LS_OK, LightScheduler_scheduleTurnOn(6, MONDAY, 600 + i));
	}
	EXPECT_EQ(LS_TOO_MANY_EVENTS, LightScheduler_scheduleTurnOn(6, MONDAY, 600 + i));
}

TEST_F(LightSchedulerTest, RemoveRecyclesScheduleSlot)
{
	int i;
	for (i = 0; i < 128; i++) {
		EXPECT_EQ(LS_OK, LightScheduler_scheduleTurnOn(6, MONDAY, 600 + i));
	}
	LightScheduler_scheduleRemove(6, MONDAY, 600);
	EXPECT_EQ(LS_OK, LightScheduler_scheduleTurnOn(13, MONDAY, 1000));
}

TEST_F(LightSchedulerTest, RemoveMultipleScheduledEvent)
{
	LightScheduler_scheduleTurnOn(6, MONDAY, 600);
	LightScheduler_scheduleTurnOn(7, MONDAY, 600);
	LightScheduler_scheduleRemove(6, MONDAY, 600);

	setTimeTo(MONDAY, 600);
	LightScheduler_wakeup();
	checkLightState(6, LIGHT_STATE_UNKNOWN);
	checkLightState(7, LIGHT_STATE_ON);
}

TEST_F(LightSchedulerTest, AcceptsValidLightIds)
{
	EXPECT_EQ(LS_OK, LightScheduler_scheduleTurnOn(0, MONDAY, 1000));
	EXPECT_EQ(LS_OK, LightScheduler_scheduleTurnOn(15, MONDAY, 1000));
	EXPECT_EQ(LS_OK, LightScheduler_scheduleTurnOn(31, MONDAY, 1000));
}

TEST_F(LightSchedulerTest, RejectsInvalidLightIds)
{
	EXPECT_EQ(LS_ID_OUT_OF_BOUNDS, LightScheduler_scheduleTurnOn(-1, MONDAY, 1000));
	EXPECT_EQ(LS_ID_OUT_OF_BOUNDS, LightScheduler_scheduleTurnOn(32, MONDAY, 1000));
}



class LightSchedulerInitAndCleanupTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
	}
	
	virtual void TearDown()
	{
	}

};

TEST_F(LightSchedulerInitAndCleanupTest, CreateStartsOneMinuteAlarm)
{
	LightScheduler_create();
	EXPECT_EQ((void*)LightScheduler_wakeup,
	                (void*)FakeTimeService_getAlarmCallback());
	EXPECT_EQ(60, FakeTimeService_getAlarmPeriod());
	LightScheduler_destroy();
}

TEST_F(LightSchedulerInitAndCleanupTest, DestroyCancelsOneMinuteAlarm)
{
	LightScheduler_create();
	LightScheduler_destroy();
	EXPECT_EQ(NULL, (void*)FakeTimeService_getAlarmCallback());
}

