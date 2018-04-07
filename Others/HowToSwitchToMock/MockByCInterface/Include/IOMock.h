#ifndef IO_MOCK_H_
#define IO_MOCK_H_

#include <stdint.h>
#include "IO.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

IO IOMock_create(int id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IO_MOCK_H_ */
