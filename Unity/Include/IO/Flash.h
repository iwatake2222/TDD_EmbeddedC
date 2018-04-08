#ifndef FLASH_H_
#define FLASH_H_

#include <IO/IO.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

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

void Flash_create();
void Flash_destroy();
int Flash_write(ioAddress address, ioData data);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FLASH_H_ */
