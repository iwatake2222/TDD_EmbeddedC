#ifndef DEVICE_DRIVER_X_H_
#define DEVICE_DRIVER_X_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define DEVICE_DRIVER_X_BASE_ADDRESS (0xF8000000)

void DeviceDriverX_create(intptr_t baseAddress);
void DeviceDriverX_destroy();
void DeviceDriverX_powerOn();


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DEVICE_DRIVER_X_H_ */
