#include <stdio.h>
#include <stdint.h>
#include "DeviceDriverX.h"
#include "IO.h"
#include "IOMock.h"


static void test_DeviceDriverX()
{
	printf("This is test code.\n");
	static int dummyReg[100];
	IOMock ioMock;
	DeviceDriverX deviceDriverX((intptr_t)dummyReg, &ioMock);
	deviceDriverX.powerOn();
}


int main()
{
	test_DeviceDriverX();

	if (0) {
		printf("This is product code.\n");

		IO io;
		DeviceDriverX deviceDriverX(&io);
		deviceDriverX.powerOn();
	}
}

