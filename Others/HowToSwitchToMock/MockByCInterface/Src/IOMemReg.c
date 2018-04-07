#include <stdint.h>
#include <stdlib.h>
#include "IOMemReg.h"
#include "IO_private.h"

typedef struct IOMemReg_t {
	struct IO_t base;
	int dummy2;
} IOMemReg_t;
typedef struct IOMemReg_t * IOMemReg;


static void IOMemReg_destroy(IO super)
{
	IOMemReg self = (IOMemReg)super;
	if (!self) free(self);
}

static void IOMemReg_write(IO super, intptr_t address, uint32_t data)
{
	IOMemReg self = (IOMemReg)super;
	*(volatile uint32_t*)address = data;
}

static uint32_t IOMemReg_read(IO super, intptr_t address)
{
	IOMemReg self = (IOMemReg)super;
	return *(volatile uint32_t*)address;
}

static IOInterface_t s_interface = {
	.destroy = IOMemReg_destroy,
	.write   = IOMemReg_write,
	.read    = IOMemReg_read,
};

IO IOMemReg_create(int id)
{
	IOMemReg self = (IOMemReg)calloc(1, sizeof(IOMemReg_t));
	self->base.vtable = &s_interface;
	self->base.type   = "IOMemReg";
	self->base.id     = id;
	return (IO)self;
}
