#include "LightControllerSpy.h"
#include "FakeTimeService.h"
#include <unity_fixture.h>

TEST_GROUP(LightControllerSpy);

TEST_SETUP(LightControllerSpy)
{
	LightController_create();
	TimeService_create();
}

TEST_TEAR_DOWN(LightControllerSpy)
{
	LightController_destroy();
	TimeService_destroy();
}

static void checkLightState(int id, int level)
{
	if (id == LIGHT_ID_UNKNOWN) {
		TEST_ASSERT_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_getLastId());
		TEST_ASSERT_EQUAL(level, LightControllerSpy_getLastState());
	} else {
		TEST_ASSERT_EQUAL(level, LightControllerSpy_getLightState(id));
	}
}

TEST(LightControllerSpy, Create)
{
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_ID_UNKNOWN);
}

TEST(LightControllerSpy, RememberTheLastLightIdControlled)
{
	LightController_on(10);
	TEST_ASSERT_EQUAL(10, LightControllerSpy_getLastId());
	checkLightState(10, LIGHT_STATE_ON);
}


TEST(LightControllerSpy, RememberAllLightStates)
{
	LightController_on(0);
	LightController_off(31);
	checkLightState(0, LIGHT_STATE_ON);
	checkLightState(31, LIGHT_STATE_OFF);
}

TEST_GROUP_RUNNER(LightControllerSpy)
{
	RUN_TEST_CASE(LightControllerSpy, Create);
	RUN_TEST_CASE(LightControllerSpy, RememberTheLastLightIdControlled);
	RUN_TEST_CASE(LightControllerSpy, RememberAllLightStates);
}

