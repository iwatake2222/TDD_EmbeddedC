#include "DeviceDriverX.h"
#include "IO.h"

#define REG_OFFSET_POWER  0x00
#define REG_OFFSET_STATUS 0x04

static intptr_t s_baseAddress = 0;
static IO_FUNC_TABLE s_ioFuncTable;

void DeviceDriverX_create(intptr_t baseAddress, IO_FUNC_TABLE *ioFuncTable)
{
	s_baseAddress = baseAddress;
	s_ioFuncTable = *ioFuncTable;
}

void DeviceDriverX_destroy()
{
}

void DeviceDriverX_powerOn()
{
	s_ioFuncTable.write(s_baseAddress + 0x00, 0xAB);
	int status;
	do {
		status = s_ioFuncTable.read(s_baseAddress + 0x04);
	} while(status == 0);
}
