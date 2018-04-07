#include "DeviceDriverX.h"
#include "IO.h"

#define REG_OFFSET_POWER  0x00
#define REG_OFFSET_STATUS 0x04

static intptr_t s_baseAddress = 0;
static IO s_io;

void DeviceDriverX_create(intptr_t baseAddress, IO io)
{
	s_baseAddress = baseAddress;
	s_io = io;
}

void DeviceDriverX_destroy()
{
	IO_destroy(s_io);
}

void DeviceDriverX_powerOn()
{
	IO_write(s_io, s_baseAddress + 0x00, 0xAB);
	int status;
	do {
		status = IO_read(s_io, s_baseAddress + 0x04);
	} while(status == 0);
}
