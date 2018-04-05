#include <stdint.h>
#include "IO.h"

void IO_write(intptr_t address, DATA_TYPE data)
{
	*(volatile DATA_TYPE*)address = data;
}

void IO_read(intptr_t address, DATA_TYPE * data)
{
	*data = *(volatile uint32_t*)address;
}

