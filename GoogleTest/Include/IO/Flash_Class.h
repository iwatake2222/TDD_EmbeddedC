#ifndef FLASH_CLASS_H_
#define FLASH_CLASS_H_

#include "IO/IIO_Class.h"

class Flash_Class {
public:
	typedef enum
	{
		FLASH_SUCCESS = 0,
		FLASH_VPP_ERROR,
		FLASH_PROGRAM_ERROR,
		FLASH_PROTECTED_BLOCK_ERROR,
		FLASH_UNKNOWN_PROGRAM_ERROR,
		FLASH_READ_BACK_ERROR,
		FLASH_TIMEOUT_ERROR
	} FLASH_STATUS;

public:
	Flash_Class(IIO_Class *io);
	~Flash_Class();
	int write(ioAddress address, ioData data);

private:
	IIO_Class* m_io;
};

#endif /* FLASH_CLASS_H_ */

