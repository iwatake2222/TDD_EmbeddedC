#include <stdint.h>
#include "IOWrapper.h"
#include "IO.h"


void IOWrapper_write(intptr_t address, uint32_t data)
{
	IO_write(address, (DATA_TYPE)data);
}

uint32_t IOWrapper_read(intptr_t address)
{
	DATA_TYPE data;
	IO_read(address, &data);
	return (uint32_t)data;
}

