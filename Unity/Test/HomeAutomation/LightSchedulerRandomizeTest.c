#include "../Mock/LightControllerSpy.h"
#include "../Mock/FakeTimeService.h"
#include "../Mock/FakeRandomMinute.h"
#include <HomeAutomation/LightScheduler.h>
#include <unity_fixture.h>

TEST_GROUP(LightSchedulerRandomizeTest);

static int (*m_savedRandomMinute_get)();

TEST_SETUP(LightSchedulerRandomizeTest)
{
	TimeService_create();
	LightController_create();
	LightScheduler_create();

	m_savedRandomMinute_get = RandomMinute_get;
	RandomMinute_get = FakeRandomMinute_get;
}

TEST_TEAR_DOWN(LightSchedulerRandomizeTest)
{
	TimeService_destroy();
	LightController_destroy();
	LightScheduler_destroy();

	RandomMinute_get = m_savedRandomMinute_get;
}


static void setTimeTo(int day, int minuteOfDay)
{
	FakeTimeService_setDay(day);
	FakeTimeService_setMinute(minuteOfDay);
}

static void checkLightState(int id, int level)
{
	// TEST_ASSERT_EQUAL(id, LightControllerSpy_getLastId());
	// TEST_ASSERT_EQUAL(level, LightControllerSpy_getLastState());
	TEST_ASSERT_EQUAL(level, LightControllerSpy_getLightState(id));
}


TEST(LightSchedulerRandomizeTest, RemoveMultipleScheduledEvent)
{
	FakeRandomMinute_setFirstandIncrement(-10, 5);
	LightScheduler_scheduleTurnOn(4, EVERYDAY, 600);
	LightScheduler_randomize(4, EVERYDAY, 600);
	setTimeTo(MONDAY, 600 - 10);
	LightScheduler_wakeup();
	checkLightState(4, LIGHT_STATE_ON);
}

/*** TEST_RUNNER (Don't forget to call RUN_TEST_GROUP) ***/
TEST_GROUP_RUNNER(LightSchedulerRandomizeTest)
{
	RUN_TEST_CASE(LightSchedulerRandomizeTest, RemoveMultipleScheduledEvent);
}
