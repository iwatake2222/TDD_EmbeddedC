#include <stdio.h>
#include <stdint.h>
#include "MyFunc.h"
#include "LedDriver/LedDriver.h"

static void sampleUsageOfLedDriver()
{
	uint16_t virtualLeds;
	LedDriver_create(&virtualLeds);
	LedDriver_turnOn(1);
	LedDriver_destroy();
}

int main()
{
	printf("This is product code.\n");

	int a = 3;
	int result;
	result = MyFunc_2X(a);
	printf("func_2X(%d) = %d\n", a, result);

	sampleUsageOfLedDriver();
}

// gcc Main.c MyFunc.c ../ExternalLibs/unity/*.c -I../ExternalLibs/unity