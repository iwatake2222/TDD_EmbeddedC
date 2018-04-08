#ifndef IO_H_
#define IO_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef uint32_t ioAddress;
typedef uint32_t ioData;

extern void (*IO_write)(ioAddress address, ioData data);
extern ioData (*IO_read)(ioAddress address);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IO_H_ */
