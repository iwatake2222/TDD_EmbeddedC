#include <stdint.h>
#include <unity_fixture.h>
#include "LedDriver/LedDriver.h"
#include "RuntimeErrorStub.h"

TEST_GROUP(LedDriver);

static uint16_t virtualLeds;

TEST_SETUP(LedDriver)
{
	LedDriver_create(&virtualLeds);
}

TEST_TEAR_DOWN(LedDriver)
{
}

TEST(LedDriver, LedsOffAfterCreate)
{
	// TEST_FAIL_MESSAGE("Start here\n");
	virtualLeds = 0xffff;
	LedDriver_create(&virtualLeds);
	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, TurnOnLedOne)
{
	LedDriver_turnOn(1);
	TEST_ASSERT_EQUAL_HEX16(1, virtualLeds);
}

TEST(LedDriver, TurnOffLedOne)
{
	LedDriver_turnOn(1);
	LedDriver_turnOff(1);
	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, TurnOnMultipleLeds)
{
	LedDriver_turnOn(9);
	LedDriver_turnOn(8);
	TEST_ASSERT_EQUAL_HEX16(0x0180, virtualLeds);
}

TEST(LedDriver, TurnOffAnyLed)
{
	LedDriver_turnAllOn();
	LedDriver_turnOff(8);
	TEST_ASSERT_EQUAL_HEX16(0xFF7F, virtualLeds);
}

IGNORE_TEST(LedDriver, AllOn)
{
	LedDriver_turnAllOn();
	TEST_ASSERT_EQUAL_HEX16(0xFFFF, virtualLeds);
}

TEST(LedDriver, LedMemoryIsNotReadable)
{
	virtualLeds = 0xffff;
	LedDriver_turnOn(8);
	TEST_ASSERT_EQUAL_HEX16(0x0080, virtualLeds);
}

TEST(LedDriver, UpperAndLowerBounds)
{
	LedDriver_turnOn(1);
	LedDriver_turnOn(16);
	TEST_ASSERT_EQUAL_HEX16(0x8001, virtualLeds);
}

TEST(LedDriver, OutOfBoundsChangesNothing)
{
	LedDriver_turnOn(-1);
	LedDriver_turnOn(0);
	LedDriver_turnOn(17);
	LedDriver_turnOn(3141);
	TEST_ASSERT_EQUAL_HEX16(0x0000, virtualLeds);
}


TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm)
{
	LedDriver_turnAllOn();
	LedDriver_turnOff(-1);
	LedDriver_turnOff(0);
	LedDriver_turnOff(17);
	LedDriver_turnOff(3141);
	TEST_ASSERT_EQUAL_HEX16(0xFFFF, virtualLeds);
}

TEST(LedDriver, OutOfBoundsProducesRuntimeError)
{
	LedDriver_turnOn(-1);
	TEST_ASSERT_EQUAL_STRING("LED Driver: out-of-bounds LED", RuntimeErrorStub_getLastError());
	TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}

TEST(LedDriver, IsOn)
{
	TEST_ASSERT_FALSE(LedDriver_isOn(11));
	LedDriver_turnOn(11);
	TEST_ASSERT_TRUE(LedDriver_isOn(11));
}

TEST(LedDriver, OutOfBoundsLedsAreAlwaysOff)
{
	TEST_ASSERT_FALSE(LedDriver_isOn(0));
	TEST_ASSERT_FALSE(LedDriver_isOn(17));
	TEST_ASSERT_FALSE(LedDriver_isOff(0));
	TEST_ASSERT_FALSE(LedDriver_isOff(17));
}

TEST(LedDriver, IsOff)
{
	TEST_ASSERT_TRUE(LedDriver_isOff(11));
	LedDriver_turnOn(11);
	TEST_ASSERT_FALSE(LedDriver_isOff(11));
}

TEST(LedDriver, TurnOffMultipleLeds)
{
	LedDriver_turnAllOn();
	LedDriver_turnOff(8);
	LedDriver_turnOff(9);
	TEST_ASSERT_EQUAL_HEX16((~0x0180) & 0xFFFF, virtualLeds);
}

TEST(LedDriver, AllOff)
{
	LedDriver_turnAllOn();
	LedDriver_turnAllOff();
	TEST_ASSERT_EQUAL_HEX16(0x0000, virtualLeds);
}

