#include <LedDriver/LedDriver.h>
#include <RuntimeErrorStub.h>
#include <CppUTest/TestHarness.h>


TEST_GROUP(LedDriver)
{
	uint16_t virtualLeds;
	void setup()
	{
		LedDriver_create(&virtualLeds);
	}

	void teardown()
	{
		LedDriver_destroy();
	}
};

TEST(LedDriver, LedsOffAfterCreate)
{
	// TEST_FAIL_MESSAGE("Start here\n");
	virtualLeds = 0xffff;
	LedDriver_create(&virtualLeds);
	LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOnLedOne)
{
	LedDriver_turnOn(1);
	LONGS_EQUAL(1, virtualLeds);
}

TEST(LedDriver, TurnOffLedOne)
{
	LedDriver_turnOn(1);
	LedDriver_turnOff(1);
	LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOnMultipleLeds)
{
	LedDriver_turnOn(9);
	LedDriver_turnOn(8);
	LONGS_EQUAL(0x0180, virtualLeds);
}

TEST(LedDriver, TurnOffAnyLed)
{
	LedDriver_turnAllOn();
	LedDriver_turnOff(8);
	LONGS_EQUAL(0xFF7F, virtualLeds);
}

IGNORE_TEST(LedDriver, AllOn)
{
	LedDriver_turnAllOn();
	LONGS_EQUAL(0xFFFF, virtualLeds);
}

TEST(LedDriver, LedMemoryIsNotReadable)
{
	virtualLeds = 0xffff;
	LedDriver_turnOn(8);
	LONGS_EQUAL(0x0080, virtualLeds);
}

TEST(LedDriver, UpperAndLowerBounds)
{
	LedDriver_turnOn(1);
	LedDriver_turnOn(16);
	LONGS_EQUAL(0x8001, virtualLeds);
}

TEST(LedDriver, OutOfBoundsChangesNothing)
{
	LedDriver_turnOn(-1);
	LedDriver_turnOn(0);
	LedDriver_turnOn(17);
	LedDriver_turnOn(3141);
	LONGS_EQUAL(0x0000, virtualLeds);
}


TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm)
{
	LedDriver_turnAllOn();
	LedDriver_turnOff(-1);
	LedDriver_turnOff(0);
	LedDriver_turnOff(17);
	LedDriver_turnOff(3141);
	LONGS_EQUAL(0xFFFF, virtualLeds);
}

TEST(LedDriver, OutOfBoundsProducesRuntimeError)
{
	LedDriver_turnOn(-1);
	STRCMP_EQUAL("LED Driver: out-of-bounds LED", RuntimeErrorStub_getLastError());
	LONGS_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}

TEST(LedDriver, IsOn)
{
	CHECK_FALSE(LedDriver_isOn(11));
	LedDriver_turnOn(11);
	CHECK_TRUE(LedDriver_isOn(11));
}

TEST(LedDriver, OutOfBoundsLedsAreAlwaysOff)
{
	CHECK_FALSE(LedDriver_isOn(0));
	CHECK_FALSE(LedDriver_isOn(17));
	CHECK_FALSE(LedDriver_isOff(0));
	CHECK_FALSE(LedDriver_isOff(17));
}

TEST(LedDriver, IsOff)
{
	CHECK_TRUE(LedDriver_isOff(11));
	LedDriver_turnOn(11);
	CHECK_FALSE(LedDriver_isOff(11));
}

TEST(LedDriver, TurnOffMultipleLeds)
{
	LedDriver_turnAllOn();
	LedDriver_turnOff(8);
	LedDriver_turnOff(9);
	LONGS_EQUAL((~0x0180) & 0xFFFF, virtualLeds);
}

TEST(LedDriver, AllOff)
{
	LedDriver_turnAllOn();
	LedDriver_turnAllOff();
	LONGS_EQUAL(0x0000, virtualLeds);
}

