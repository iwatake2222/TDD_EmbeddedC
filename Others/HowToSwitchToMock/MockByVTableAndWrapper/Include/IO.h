#ifndef IO_H_
#define IO_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef uint16_t DATA_TYPE;

void IO_write(intptr_t address, DATA_TYPE data);
void IO_read(intptr_t address, DATA_TYPE * data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IO_H_ */
