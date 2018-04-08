#ifndef m28w160ect_H_
#define m28w160ect_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum
{
	COMMAND_REGISTER = 0x0,
	STATUS_REGISTER  = 0x0
} FLASH_REGISTERS;

typedef enum
{
	PROGRAM_COMMAND = 0x40,
	RESET_COMMAND   = 0xff
} FLASH_COMMAND;

typedef enum
{
	READY_BIT                  = 1 << 7,
	ERASE_SUSPEND_BIT          = 1 << 6,
	ERASE_ERROR_BIT            = 1 << 5,
	PROGRAM_ERROR_BIT          = 1 << 4,
	VPP_ERROR_BIT              = 1 << 3,
	PROGRAM_SUSPEND_BIT        = 1 << 2,
	BLOCK_PROTECTION_ERROR_BIT = 1 << 1,
	REVERSED_BIT               = 1 << 0,
} STATUS_REGISTER_BITS;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* m28w160ect_H_ */
