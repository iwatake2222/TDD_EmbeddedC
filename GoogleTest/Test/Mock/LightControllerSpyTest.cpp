#include "LightControllerSpy.h"
#include "FakeTimeService.h"
#include "gtest/gtest.h"

class LightControllerSpyTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		LightController_create();
		TimeService_create();
	}
	
	virtual void TearDown()
	{
		LightController_destroy();
		TimeService_destroy();
	}

	void checkLightState(int id, int level)
	{
		if (id == LIGHT_ID_UNKNOWN) {
			EXPECT_EQ(LIGHT_ID_UNKNOWN, LightControllerSpy_getLastId());
			EXPECT_EQ(level, LightControllerSpy_getLastState());
		} else {
			EXPECT_EQ(level, LightControllerSpy_getLightState(id));
		}
	}
};

TEST_F(LightControllerSpyTest, Create)
{
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_ID_UNKNOWN);
}

TEST_F(LightControllerSpyTest, RememberTheLastLightIdControlled)
{
	LightController_on(10);
	EXPECT_EQ(10, LightControllerSpy_getLastId());
	checkLightState(10, LIGHT_STATE_ON);
}


TEST_F(LightControllerSpyTest, RememberAllLightStates)
{
	LightController_on(0);
	LightController_off(31);
	checkLightState(0, LIGHT_STATE_ON);
	checkLightState(31, LIGHT_STATE_OFF);
}

