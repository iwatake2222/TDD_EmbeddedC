#ifndef OS_WRAPPER_H_
#define OS_WRAPPER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct {
	int (*getTime)();
	int (*sendMsg)(int queue, void* msg);
	int (*recvMsg)(int queue, void* msg);
} OS_FUNC;

extern OS_FUNC os;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OS_WRAPPER_H_ */
