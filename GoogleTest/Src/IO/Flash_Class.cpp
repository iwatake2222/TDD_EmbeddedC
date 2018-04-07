#include <stdio.h>
#include "IO/Flash_Class.h"
#include "IO/IIO_Class.h"
#include "IO/m28w160ect.h"
#include "Util/MicroTime.h"

#define FLASH_WRITE_TIMEOUT_IN_MICROSECONDS 5000

Flash_Class::Flash_Class(IIO_Class *io)
	: m_io(io)
{
}

Flash_Class::~Flash_Class()
{
}

int Flash_Class::write(ioAddress address, ioData data)
{
	ioData status = 0;
	int timestamp = MicroTime_get();

	m_io->write(COMMAND_REGISTER, PROGRAM_COMMAND);
	m_io->write(address, data);
	do {
		if (MicroTime_get() - timestamp > FLASH_WRITE_TIMEOUT_IN_MICROSECONDS) return FLASH_TIMEOUT_ERROR;
		status = m_io->read(STATUS_REGISTER);
	} while((status & READY_BIT) == 0);

	if (status != READY_BIT) {
		m_io->write(COMMAND_REGISTER, RESET_COMMAND);
		if (status & VPP_ERROR_BIT) return FLASH_VPP_ERROR;
		if (status & PROGRAM_ERROR_BIT) return FLASH_PROGRAM_ERROR;
		if (status & BLOCK_PROTECTION_ERROR_BIT) return FLASH_PROTECTED_BLOCK_ERROR;
		return FLASH_UNKNOWN_PROGRAM_ERROR;
	}
	
	if (data != m_io->read(address)) return FLASH_READ_BACK_ERROR;
	return FLASH_SUCCESS;
}

