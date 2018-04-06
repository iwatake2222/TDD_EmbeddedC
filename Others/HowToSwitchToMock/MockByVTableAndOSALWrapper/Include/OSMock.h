#ifndef OS_MOCK_H_
#define OS_MOCK_H_

#include "OSWrapper.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void OSMock_create();
void OSMock_destroy();
void OSMock_initTime(int start, int increment);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OS_MOCK_H_ */

