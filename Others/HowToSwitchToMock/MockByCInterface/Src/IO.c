#include <stdint.h>
#include "IO.h"
#include "IO_private.h"

void IO_destroy(IO self)
{
	if (self && self->vtable && self->vtable->destroy)
		self->vtable->destroy(self);
}

void IO_write(IO self, intptr_t address, uint32_t data)
{
	if (self && self->vtable && self->vtable->destroy)
		self->vtable->write(self, address, data);
}

uint32_t IO_read(IO self, intptr_t address)
{
	if (self && self->vtable && self->vtable->destroy)
		return self->vtable->read(self, address);
	return 0;
}


