#include <stdint.h>
#include <stdio.h>
#include "IOMock.h"

IOMock::IOMock()
{
}

IOMock::~IOMock()
{
}

void IOMock::write(intptr_t address, uint32_t data)
{
	printf("MociIO_write(Address = %08X, Data = %08X)\n", address, data);
}

uint32_t IOMock::read(intptr_t address)
{
	printf("MociIO_read(Address = %08X)\n", address);
	return 1;
}

