#include "../Mock/LightControllerSpy.h"
#include "../Mock/FakeTimeService.h"
#include <HomeAutomation/LightScheduler.h>
#include <CppUTest/TestHarness.h>

TEST_GROUP(LightScheduler)
{
	void setup()
	{
		TimeService_create();
		LightController_create();
		LightScheduler_create();
	}

	void teardown()
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
		// LONGS_EQUAL(id, LightControllerSpy_getLastId());
		// LONGS_EQUAL(level, LightControllerSpy_getLastState());
		LONGS_EQUAL(level, LightControllerSpy_getLightState(id));
	}
};

TEST(LightScheduler, NoChangeToLightsDuringInitialization)
{
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, NoSchedulerNothingHappens)
{
	setTimeTo(MONDAY, 100);
	LightScheduler_wakeup();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}


TEST(LightScheduler, ScheduleOnEverydayNotTimeYet)
{
	LightScheduler_scheduleTurnOn(3, EVERYDAY, 1200);
	setTimeTo(MONDAY, 1199);
	LightScheduler_wakeup();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnEverydayItsTime)
{
	LightScheduler_scheduleTurnOn(3, EVERYDAY, 1200);
	setTimeTo(MONDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(3, LIGHT_STATE_ON);
}

TEST(LightScheduler, ScheduleOffEverydayItsTime)
{
	LightScheduler_scheduleTurnOff(3, EVERYDAY, 1200);
	setTimeTo(MONDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(3, LIGHT_STATE_OFF);
}

TEST(LightScheduler, ScheduleTuesdayButItsMonday)
{
	LightScheduler_scheduleTurnOff(3, TUESDAY, 1200);
	setTimeTo(MONDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleTuesdayAndItsTuesday)
{
	LightScheduler_scheduleTurnOn(3, TUESDAY, 1200);
	setTimeTo(TUESDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(3, LIGHT_STATE_ON);
}

TEST(LightScheduler, ScheduleWeekEndItsFriday)
{
	LightScheduler_scheduleTurnOn(3, WEEKEND, 1200);
	setTimeTo(FRIDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleWeekEndItsSaturday)
{
	LightScheduler_scheduleTurnOn(3, WEEKEND, 1200);
	setTimeTo(SATURDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(3, LIGHT_STATE_ON);
}

TEST(LightScheduler, ScheduleWeekEndItsSunday)
{
	LightScheduler_scheduleTurnOn(3, WEEKEND, 1200);
	setTimeTo(SUNDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(3, LIGHT_STATE_ON);
}

TEST(LightScheduler, ScheduleWeekEndItsMonday)
{
	LightScheduler_scheduleTurnOn(3, WEEKEND, 1200);
	setTimeTo(MONDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleWeekDayItsSunday)
{
	LightScheduler_scheduleTurnOn(3, WEEKDAY, 1200);
	setTimeTo(SUNDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleWeekDayItsSaturday)
{
	LightScheduler_scheduleTurnOn(3, WEEKDAY, 1200);
	setTimeTo(SATURDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleWeekDayItsMonday)
{
	LightScheduler_scheduleTurnOn(3, WEEKDAY, 1200);
	setTimeTo(MONDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(3, LIGHT_STATE_ON);
}

TEST(LightScheduler, ScheduleWeekDayItsFriday)
{
	LightScheduler_scheduleTurnOn(3, WEEKDAY, 1200);
	setTimeTo(FRIDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(3, LIGHT_STATE_ON);
}

TEST(LightScheduler, ScheduleTwoEventsAtTheSameTime)
{
	LightScheduler_scheduleTurnOn(3, SUNDAY, 1200);
	LightScheduler_scheduleTurnOff(12, SUNDAY, 1200);
	setTimeTo(SUNDAY, 1200);
	LightScheduler_wakeup();
	checkLightState(3, LIGHT_STATE_ON);
	checkLightState(12, LIGHT_STATE_OFF);
}

TEST(LightScheduler, RejectTooManyEvents)
{
	int i;
	for (i = 0; i < 128; i++) {
		LONGS_EQUAL(LS_OK, LightScheduler_scheduleTurnOn(6, MONDAY, 600 + i));
	}
	LONGS_EQUAL(LS_TOO_MANY_EVENTS, LightScheduler_scheduleTurnOn(6, MONDAY, 600 + i));
}

TEST(LightScheduler, RemoveRecyclesScheduleSlot)
{
	int i;
	for (i = 0; i < 128; i++) {
		LONGS_EQUAL(LS_OK, LightScheduler_scheduleTurnOn(6, MONDAY, 600 + i));
	}
	LightScheduler_scheduleRemove(6, MONDAY, 600);
	LONGS_EQUAL(LS_OK, LightScheduler_scheduleTurnOn(13, MONDAY, 1000));
}

TEST(LightScheduler, RemoveMultipleScheduledEvent)
{
	LightScheduler_scheduleTurnOn(6, MONDAY, 600);
	LightScheduler_scheduleTurnOn(7, MONDAY, 600);
	LightScheduler_scheduleRemove(6, MONDAY, 600);

	setTimeTo(MONDAY, 600);
	LightScheduler_wakeup();
	checkLightState(6, LIGHT_STATE_UNKNOWN);
	checkLightState(7, LIGHT_STATE_ON);
}

TEST(LightScheduler, AcceptsValidLightIds)
{
	LONGS_EQUAL(LS_OK, LightScheduler_scheduleTurnOn(0, MONDAY, 1000));
	LONGS_EQUAL(LS_OK, LightScheduler_scheduleTurnOn(15, MONDAY, 1000));
	LONGS_EQUAL(LS_OK, LightScheduler_scheduleTurnOn(31, MONDAY, 1000));
}

TEST(LightScheduler, RejectsInvalidLightIds)
{
	LONGS_EQUAL(LS_ID_OUT_OF_BOUNDS, LightScheduler_scheduleTurnOn(-1, MONDAY, 1000));
	LONGS_EQUAL(LS_ID_OUT_OF_BOUNDS, LightScheduler_scheduleTurnOn(32, MONDAY, 1000));
}


TEST_GROUP(LightSchedulerInitAndCleanup)
{
	void setup()
	{
	}

	void teardown()
	{
	}
};

TEST(LightSchedulerInitAndCleanup, CreateStartsOneMinuteAlarm)
{
	LightScheduler_create();
	POINTERS_EQUAL((void*)LightScheduler_wakeup,
	                (void*)FakeTimeService_getAlarmCallback());
	LONGS_EQUAL(60, FakeTimeService_getAlarmPeriod());
	LightScheduler_destroy();
}

TEST(LightSchedulerInitAndCleanup, DestroyCancelsOneMinuteAlarm)
{
	LightScheduler_create();
	LightScheduler_destroy();
	POINTERS_EQUAL(NULL, (void*)FakeTimeService_getAlarmCallback());
}

