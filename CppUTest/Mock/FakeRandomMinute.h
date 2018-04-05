#ifndef FAKE_RANDOM_MINUTE_H_
#define FAKE_RANDOM_MINUTE_H_

#include <HomeAutomation/RandomMinute.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void FakeRandomMinute_setFirstandIncrement(int initialValue, int delta);
int FakeRandomMinute_get();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FAKE_RANDOM_MINUTE_H_ */
