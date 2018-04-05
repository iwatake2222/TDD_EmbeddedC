#include <stdio.h>
#include <stdint.h>
#include "DeviceDriverX.h"
#include "IOWrapper.h"

static void MockIO_write(intptr_t address, uint32_t data)
{
	printf("MociIO_write(Address = %08X, Data = %08X)\n", address, data);
}

static uint32_t MockIO_read(intptr_t address)
{
	printf("MociIO_read(Address = %08X)\n", address);
	return 1;
}

static void test_DeviceDriverX()
{
	static int dummyReg[100];

	IO_FUNC_TABLE ioFuncTable = {
		.write = MockIO_write,
		.read  = MockIO_read,
	};
	DeviceDriverX_create((intptr_t)dummyReg, &ioFuncTable);
	DeviceDriverX_powerOn();
	DeviceDriverX_destroy();
}


int main()
{
	test_DeviceDriverX();

	if (0) {
		printf("This is product code.\n");

		IO_FUNC_TABLE ioFuncTable = {
			.write = IOWrapper_write,
			.read  = IOWrapper_read,
		};
		DeviceDriverX_create((intptr_t)DEVICE_DRIVER_X_BASE_ADDRESS, &ioFuncTable);
		DeviceDriverX_powerOn();
		DeviceDriverX_destroy();
	}
}

