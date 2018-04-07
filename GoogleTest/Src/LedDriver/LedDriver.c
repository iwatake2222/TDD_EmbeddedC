#include "LedDriver/LedDriver.h"
#include "Util/RuntimeError.h"

static uint16_t* ledsAddress;
static uint16_t ledsImage;
enum {
	ALL_LEDS_ON = ~0,
	ALL_LEDS_OFF = ~ALL_LEDS_ON,
};

enum {
	FIRST_LED = 1,
	LAST_LED = 16,
};

static uint16_t convertLedNumberToBit(int ledNumber)
{
	return 1 << (ledNumber - 1);;
}

static void setLedImageBit(int ledNumber)
{
	ledsImage |= convertLedNumberToBit(ledNumber);
}

static void clearLedImageBit(int ledNumber)
{
	ledsImage &= ~(convertLedNumberToBit(ledNumber));
}

static void updateHardware()
{
	*ledsAddress = ledsImage;
}

static int isLedOutOfBounds(int ledNumber)
{
	return (ledNumber < FIRST_LED || LAST_LED < ledNumber);
}

void LedDriver_create(uint16_t* address)
{
	ledsAddress = address;
	ledsImage = ALL_LEDS_OFF;
	updateHardware();
}

void LedDriver_destroy()
{
}

void LedDriver_turnOn(int ledNumber)
{
	if (isLedOutOfBounds(ledNumber)) {
		RUNTIME_ERROR("LED Driver: out-of-bounds LED", -1);
		return;
	}
	
	setLedImageBit(ledNumber);
	updateHardware();
}

void LedDriver_turnOff(int ledNumber)
{
	if (isLedOutOfBounds(ledNumber)) {
		RUNTIME_ERROR("LED Driver: out-of-bounds LED", -1);
		return;
	}
	clearLedImageBit(ledNumber);
	updateHardware();
}

void LedDriver_turnAllOn()
{
	ledsImage = ALL_LEDS_ON;
	updateHardware();
}

void LedDriver_turnAllOff()
{
	ledsImage = ALL_LEDS_OFF;
	updateHardware();
}

int  LedDriver_isOn(int ledNumber)
{
	if (isLedOutOfBounds(ledNumber)) {
		RUNTIME_ERROR("LED Driver: out-of-bounds LED", -1);
		return 0;
	}
	return 0 != (ledsImage & convertLedNumberToBit(ledNumber));
}

int  LedDriver_isOff(int ledNumber)
{
	if (isLedOutOfBounds(ledNumber)) {
		RUNTIME_ERROR("LED Driver: out-of-bounds LED", -1);
		return 0;
	}
	return 0 == (ledsImage & convertLedNumberToBit(ledNumber));
}
