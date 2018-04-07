#ifndef IO_H_
#define IO_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct IO_t * IO;

void IO_destroy(IO self);
void IO_write(IO self, intptr_t address, uint32_t data);
uint32_t IO_read(IO self, intptr_t address);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IO_H_ */
