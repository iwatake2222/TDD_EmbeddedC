#include "../Mock/LightControllerSpy.h"
#include "../Mock/FakeTimeService.h"
#include "../Mock/FakeRandomMinute.h"
#include <HomeAutomation/LightScheduler.h>

#include <CppUTest/TestHarness.h>

TEST_GROUP(LightSchedulerRandomizeTest)
{
	int (*m_savedRandomMinute_get)();
	void setup()
	{
		TimeService_create();
		LightController_create();
		LightScheduler_create();

		m_savedRandomMinute_get = RandomMinute_get;
		RandomMinute_get = FakeRandomMinute_get;
	}

	void teardown()
	{
		TimeService_destroy();
		LightController_destroy();
		LightScheduler_destroy();

		RandomMinute_get = m_savedRandomMinute_get;
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


TEST(LightSchedulerRandomizeTest, RemoveMultipleScheduledEvent)
{
	FakeRandomMinute_setFirstandIncrement(-10, 5);
	LightScheduler_scheduleTurnOn(4, EVERYDAY, 600);
	LightScheduler_randomize(4, EVERYDAY, 600);
	setTimeTo(MONDAY, 600 - 10);
	LightScheduler_wakeup();
	checkLightState(4, LIGHT_STATE_ON);
}
