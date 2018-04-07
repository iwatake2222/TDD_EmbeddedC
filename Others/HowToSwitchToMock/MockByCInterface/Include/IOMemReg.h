#ifndef IO_MEMREG_H_
#define IO_MEMREG_H_

#include <stdint.h>
#include "IO.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

IO IOMemReg_create(int id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IO_MEMREG_H_ */
