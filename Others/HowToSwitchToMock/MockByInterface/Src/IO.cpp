#include <stdint.h>
#include "IO.h"

IO::IO()
{
}

IO::~IO()
{
}

void IO::write(intptr_t address, uint32_t data)
{
	*(volatile uint32_t*)address = data;
}

uint32_t IO::read(intptr_t address)
{
	return *(volatile uint32_t*)address;
}

