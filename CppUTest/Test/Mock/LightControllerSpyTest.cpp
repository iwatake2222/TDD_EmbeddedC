#include "LightControllerSpy.h"
#include "FakeTimeService.h"
#include <CppUTest/TestHarness.h>

TEST_GROUP(LightControllerSpy)
{
	void setup()
	{
		LightController_create();
		TimeService_create();
	}

	void teardown()
	{
		LightController_destroy();
		TimeService_destroy();
	}

	void checkLightState(int id, int level)
	{
		if (id == LIGHT_ID_UNKNOWN) {
			LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_getLastId());
			LONGS_EQUAL(level, LightControllerSpy_getLastState());
		} else {
			LONGS_EQUAL(level, LightControllerSpy_getLightState(id));
		}
	}
};

TEST(LightControllerSpy, Create)
{
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_ID_UNKNOWN);
}

TEST(LightControllerSpy, RememberTheLastLightIdControlled)
{
	LightController_on(10);
	LONGS_EQUAL(10, LightControllerSpy_getLastId());
	checkLightState(10, LIGHT_STATE_ON);
}


TEST(LightControllerSpy, RememberAllLightStates)
{
	LightController_on(0);
	LightController_off(31);
	checkLightState(0, LIGHT_STATE_ON);
	checkLightState(31, LIGHT_STATE_OFF);
}

