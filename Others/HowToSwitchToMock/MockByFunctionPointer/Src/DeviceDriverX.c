#include "IO.h"

#define REG_OFFSET_POWER  0x00
#define REG_OFFSET_STATUS 0x04

static intptr_t s_baseAddress = 0;

void DeviceDriverX_create(intptr_t baseAddress)
{
	s_baseAddress = baseAddress;
}

void DeviceDriverX_destroy()
{
}

void DeviceDriverX_powerOn()
{
	IO_write(s_baseAddress + 0x00, 0xAB);
	int status;
	do {
		status = IO_read(s_baseAddress + 0x04);
	} while(status == 0);
}
