#ifndef FAKE_MICRO_TIME_H_
#define FAKE_MICRO_TIME_H_

#include <Util/MicroTime.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int FakeMicroTime_init(int start, int incr);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FAKE_MICRO_TIME_H_ */
