#include <stdio.h>
#include "IO/IO_Class.h"

IO_Class::IO_Class()
{
}

IO_Class::~IO_Class()
{
}

void IO_Class::write(ioAddress address, ioData data)
{
	ioData * p = 0;
	*(p + address) = data;
}

ioData IO_Class::read(ioAddress address)
{
	ioData * p = 0;
	return *(p + address);
}