#include <stdio.h>
#include <stdint.h>

#include <LedDriver/LedDriver.h>


int main()
{
	printf("This is product code.\n");

	LedDriver_create(0x00);
}

