#ifndef DEVICE_DRIVER_X_H_
#define DEVICE_DRIVER_X_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define DEVICE_DRIVER_X_BASE_ADDRESS (0xF8000000)

typedef struct {
	void (*write)(intptr_t address, uint32_t data);
	uint32_t (*read)(intptr_t address);
} IO_FUNC_TABLE;

void DeviceDriverX_create(intptr_t baseAddress, IO_FUNC_TABLE *ioFuncTable);
void DeviceDriverX_destroy();
void DeviceDriverX_powerOn();


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DEVICE_DRIVER_X_H_ */
