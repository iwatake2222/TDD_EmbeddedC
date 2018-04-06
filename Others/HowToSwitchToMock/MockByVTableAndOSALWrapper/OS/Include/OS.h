#ifndef OS_H_
#define OS_H_

#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int OS_getTime(time_t* time);
int OS_sendMsg(int queue, void* msg);
int OS_recvMsg(int queue, void* msg);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OS_H_ */
