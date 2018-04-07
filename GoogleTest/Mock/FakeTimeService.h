#ifndef FAKE_TIME_SERVICE_H_
#define FAKE_TIME_SERVICE_H_

#include <Util/TimeService.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void FakeTimeService_setMinute(int minuteOfDay);
void FakeTimeService_setDay(int dayOfWeek);
WakeupCallback FakeTimeService_getAlarmCallback();
int FakeTimeService_getAlarmPeriod();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FAKE_TIME_SERVICE_H_ */
