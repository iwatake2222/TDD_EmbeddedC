#include <stdio.h>
#include <stdint.h>
#include "DeviceDriverX.h"
#include "IO.h"

static void MociIO_write(intptr_t address, uint32_t data)
{
	printf("MociIO_write(Address = %08X, Data = %08X)\n", address, data);
}

static uint32_t MociIO_read(intptr_t address)
{
	printf("MociIO_read(Address = %08X)\n", address);
	return 1;
}

static void test_DeviceDriverX()
{
	static int dummyReg[100];
	IO_write = MociIO_write;
	IO_read = MociIO_read;

	DeviceDriverX_create((intptr_t)dummyReg);
	DeviceDriverX_powerOn();
	DeviceDriverX_destroy();
}


int main()
{
	test_DeviceDriverX();

	if (0) {
		printf("This is product code.\n");

		DeviceDriverX_create((intptr_t)DEVICE_DRIVER_X_BASE_ADDRESS);
		DeviceDriverX_powerOn();
		DeviceDriverX_destroy();
	}
}

