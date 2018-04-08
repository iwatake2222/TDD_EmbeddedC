#ifndef TIME_SERVICE_H_
#define TIME_SERVICE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum {
	TIME_UNKNOWN,
};

typedef enum {
	NONE = -1,
	EVERYDAY = 10,
	WEEKDAY,
	WEEKEND,
	SUNDAY = 1,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
} DAY;

typedef struct {
	int minuteOfDay;
	int dayOfWeek;
} Time;

void TimeService_create();
void TimeService_destroy();
void TimeService_getTime(Time *time);

typedef void(*WakeupCallback)(void);
void TimeService_setPeriodicAlarmInSecond(int seconds, WakeupCallback cb);
void TimeService_cancelPeriodicAlarmInSecond(int seconds, WakeupCallback cb);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TIME_SERVICE_H_ */
