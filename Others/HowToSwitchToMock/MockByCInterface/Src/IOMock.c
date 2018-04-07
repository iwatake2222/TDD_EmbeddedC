#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "IOMock.h"
#include "IO_private.h"

typedef struct IOMock_t {
	struct IO_t base;
	int dummy2;
} IOMock_t;
typedef struct IOMock_t * IOMock;

static int dummyReg[100];

static void IOMock_destroy(IO super)
{
	IOMock self = (IOMock)super;
	if (!self) free(self);
}

static void IOMock_write(IO super, intptr_t address, uint32_t data)
{
	IOMock self = (IOMock)super;
	printf("MociIO_write(Address = %08X, Data = %08X)\n", address, data);
	dummyReg[address%100] = data;
}

static uint32_t IOMock_read(IO super, intptr_t address)
{
	IOMock self = (IOMock)super;
	printf("MociIO_read(Address = %08X)\n", address);
	// return dummyReg[address%100];
	return 1;
}

static IOInterface_t s_interface = {
	.destroy = IOMock_destroy,
	.write   = IOMock_write,
	.read    = IOMock_read,
};

IO IOMock_create(int id)
{
	IOMock self = (IOMock)calloc(1, sizeof(IOMock_t));
	self->base.vtable = &s_interface;
	self->base.type   = "IOMock";
	self->base.id     = id;
	return (IO)self;
}
