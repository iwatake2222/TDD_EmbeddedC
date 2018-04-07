#include <stdio.h>
#include <stdint.h>
#include "DeviceDriverX.h"
#include "IO.h"
#include "IOMemReg.h"
#include "IOMock.h"



static void test_DeviceDriverX()
{
	printf("This is test code.\n");
	int dummyReg[100];
	IO io = IOMock_create(2);
	DeviceDriverX_create((intptr_t)dummyReg, io);
	DeviceDriverX_powerOn();
	DeviceDriverX_destroy();
}


int main()
{
	test_DeviceDriverX();

	if (0) {
		printf("This is product code.\n");

		IO io = IOMemReg_create(1);
		DeviceDriverX_create((intptr_t)DEVICE_DRIVER_X_BASE_ADDRESS, io);
		DeviceDriverX_powerOn();
		DeviceDriverX_destroy();
	}
}

