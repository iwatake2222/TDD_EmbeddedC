#include <LedDriver/LedDriver.h>
#include <RuntimeErrorStub.h>
#include "gtest/gtest.h"

class LedDriverTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		LedDriver_create(&virtualLeds);
	}
	
	virtual void TearDown()
	{
		LedDriver_destroy();
	}

	uint16_t virtualLeds;
};


TEST_F(LedDriverTest, LedsOffAfterCreate)
{
	// TEST_F_FAIL_MESSAGE("Start here\n");
	virtualLeds = 0xffff;
	LedDriver_create(&virtualLeds);
	EXPECT_EQ(0, virtualLeds);
}

TEST_F(LedDriverTest, TurnOnLedOne)
{
	LedDriver_turnOn(1);
	EXPECT_EQ(1, virtualLeds);
}

TEST_F(LedDriverTest, TurnOffLedOne)
{
	LedDriver_turnOn(1);
	LedDriver_turnOff(1);
	EXPECT_EQ(0, virtualLeds);
}

TEST_F(LedDriverTest, TurnOnMultipleLeds)
{
	LedDriver_turnOn(9);
	LedDriver_turnOn(8);
	EXPECT_EQ(0x0180, virtualLeds);
}

TEST_F(LedDriverTest, TurnOffAnyLed)
{
	LedDriver_turnAllOn();
	LedDriver_turnOff(8);
	EXPECT_EQ(0xFF7F, virtualLeds);
}

TEST_F(LedDriverTest, DISABLED_AllOn)
{
	LedDriver_turnAllOn();
	EXPECT_EQ(0xFFFF, virtualLeds);
}

TEST_F(LedDriverTest, LedMemoryIsNotReadable)
{
	virtualLeds = 0xffff;
	LedDriver_turnOn(8);
	EXPECT_EQ(0x0080, virtualLeds);
}

TEST_F(LedDriverTest, UpperAndLowerBounds)
{
	LedDriver_turnOn(1);
	LedDriver_turnOn(16);
	EXPECT_EQ(0x8001, virtualLeds);
}

TEST_F(LedDriverTest, OutOfBoundsChangesNothing)
{
	LedDriver_turnOn(-1);
	LedDriver_turnOn(0);
	LedDriver_turnOn(17);
	LedDriver_turnOn(3141);
	EXPECT_EQ(0x0000, virtualLeds);
}


TEST_F(LedDriverTest, OutOfBoundsTurnOffDoesNoHarm)
{
	LedDriver_turnAllOn();
	LedDriver_turnOff(-1);
	LedDriver_turnOff(0);
	LedDriver_turnOff(17);
	LedDriver_turnOff(3141);
	EXPECT_EQ(0xFFFF, virtualLeds);
}

TEST_F(LedDriverTest, OutOfBoundsProducesRuntimeError)
{
	LedDriver_turnOn(-1);
	EXPECT_STREQ("LED Driver: out-of-bounds LED", RuntimeErrorStub_getLastError());
	EXPECT_EQ(-1, RuntimeErrorStub_GetLastParameter());
}

TEST_F(LedDriverTest, IsOn)
{
	EXPECT_FALSE(LedDriver_isOn(11));
	LedDriver_turnOn(11);
	EXPECT_TRUE(LedDriver_isOn(11));
}

TEST_F(LedDriverTest, OutOfBoundsLedsAreAlwaysOff)
{
	EXPECT_FALSE(LedDriver_isOn(0));
	EXPECT_FALSE(LedDriver_isOn(17));
	EXPECT_FALSE(LedDriver_isOff(0));
	EXPECT_FALSE(LedDriver_isOff(17));
}

TEST_F(LedDriverTest, IsOff)
{
	EXPECT_TRUE(LedDriver_isOff(11));
	LedDriver_turnOn(11);
	EXPECT_FALSE(LedDriver_isOff(11));
}

TEST_F(LedDriverTest, TurnOffMultipleLeds)
{
	LedDriver_turnAllOn();
	LedDriver_turnOff(8);
	LedDriver_turnOff(9);
	EXPECT_EQ((~0x0180) & 0xFFFF, virtualLeds);
}

TEST_F(LedDriverTest, AllOff)
{
	LedDriver_turnAllOn();
	LedDriver_turnAllOff();
	EXPECT_EQ(0x0000, virtualLeds);
}

