#ifndef IO_WRAPPER_H_
#define IO_WRAPPER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void IOWrapper_write(intptr_t address, uint32_t data);
uint32_t IOWrapper_read(intptr_t address);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IO_WRAPPER_H_ */
