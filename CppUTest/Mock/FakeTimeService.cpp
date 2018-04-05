#include <stdio.h>
#include "FakeTimeService.h"

/*****************************************
 * Data containers and accessors
 *****************************************/
static Time s_time;
static WakeupCallback s_callback;
static int s_period;

void FakeTimeService_setMinute(int minuteOfDay)
{
	s_time.minuteOfDay = minuteOfDay;
}

void FakeTimeService_setDay(int dayOfWeek)
{
	s_time.dayOfWeek = dayOfWeek;
}

WakeupCallback FakeTimeService_getAlarmCallback()
{
	return s_callback;
}

int FakeTimeService_getAlarmPeriod()
{
	return s_period;
}

/*****************************************
 * Mock functions
 *****************************************/
void TimeService_create()
{
	s_time.minuteOfDay = TIME_UNKNOWN;
	s_time.dayOfWeek = TIME_UNKNOWN;
}

void TimeService_destroy()
{
}

void TimeService_getTime(Time *time)
{
	time->minuteOfDay = s_time.minuteOfDay;
	time->dayOfWeek = s_time.dayOfWeek;
}

void TimeService_setPeriodicAlarmInSecond(int seconds, WakeupCallback cb)
{
	s_callback = cb;
	s_period = seconds;
}

void TimeService_cancelPeriodicAlarmInSecond(int seconds, WakeupCallback cb)
{
	if (cb == s_callback && seconds == s_period) {
		s_callback = NULL;
		s_period = 0;
	}
}