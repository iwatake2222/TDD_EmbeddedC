#include <stdint.h>
#include <IO.h>

void IO_write(intptr_t address, uint32_t data)
{
	*(volatile uint32_t*)address = data;
}

uint32_t IO_read(intptr_t address)
{
	return *(volatile uint32_t*)address;
}

