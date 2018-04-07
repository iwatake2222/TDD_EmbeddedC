#include <Util/TimeService.h>
#include <HomeAutomation/LightScheduler.h>
#include <HomeAutomation/LightController.h>
#include <HomeAutomation/RandomMinute.h>

enum {
	UNKNOWN,
	TURN_ON,
	TURN_OFF,
};

#define MAX_EVENT_NUM 128

typedef struct {
	int id;
	int event;
	DAY day;
	int minuteOfDay;
} ScheduledLightEvent;

static ScheduledLightEvent s_scheduledEvents[MAX_EVENT_NUM];

static int scheduleEvent(int id, DAY day, int minuteOfDay, int event)
{
	if (id < 0 || 31 < id) return LS_ID_OUT_OF_BOUNDS;
	for (int i = 0; i < MAX_EVENT_NUM; i++) {
		if (s_scheduledEvents[i].id == UNKNOWN) {
			s_scheduledEvents[i].id = id;
			s_scheduledEvents[i].event = event;
			s_scheduledEvents[i].day = day;
			s_scheduledEvents[i].minuteOfDay = minuteOfDay;
			return LS_OK;
		}
	}
	return LS_TOO_MANY_EVENTS;
}

void LightScheduler_create()
{
	for (int i = 0; i < MAX_EVENT_NUM; i++) s_scheduledEvents[i].id = UNKNOWN;
	TimeService_setPeriodicAlarmInSecond(60, LightScheduler_wakeup);
}

void LightScheduler_destroy()
{
	TimeService_cancelPeriodicAlarmInSecond(60, LightScheduler_wakeup);
}

int LightScheduler_scheduleTurnOn(int id, DAY day, int minuteOfDay)
{
	return scheduleEvent(id, day, minuteOfDay, TURN_ON);
}

int LightScheduler_scheduleTurnOff(int id, DAY day, int minuteOfDay)
{
	return scheduleEvent(id, day, minuteOfDay, TURN_OFF);
}

int LightScheduler_scheduleRemove(int id, DAY day, int minuteOfDay)
{
	for (int i = 0; i < MAX_EVENT_NUM; i++) {
		if (s_scheduledEvents[i].id == id
		 && s_scheduledEvents[i].day == day
		 && s_scheduledEvents[i].minuteOfDay == minuteOfDay) {
			s_scheduledEvents[i].id = UNKNOWN;
			return LS_OK;
		}
	}
	return LS_ITEM_NOT_FOUND;
}

static void operateLight(ScheduledLightEvent *lightEvent)
{
	if (lightEvent->event == TURN_ON) {
		LightController_on(lightEvent->id);
	} else if (lightEvent->event == TURN_OFF) {
		LightController_off(lightEvent->id);
	}
}

static bool doesLightRespondToday(Time *time, int reactionDay)
{
	int today = time->dayOfWeek;
	if (reactionDay == EVERYDAY) return true;
	if (reactionDay == today) return true;
	if (reactionDay == WEEKEND && (today == SATURDAY || today == SUNDAY)) return true;
	if (reactionDay == WEEKDAY && (MONDAY <= today && today <= FRIDAY)) return true;
	return false;
}

static void processEventDueNow(Time *time, ScheduledLightEvent *lightEvent)
{

	if (lightEvent->id == UNKNOWN) return;
	if(!doesLightRespondToday(time, lightEvent->day)) return;
	if (lightEvent->minuteOfDay != time->minuteOfDay) return;

	operateLight(lightEvent);
}


void LightScheduler_wakeup()
{
	Time time;
	TimeService_getTime(&time);

	for (int i = 0; i < MAX_EVENT_NUM; i++) processEventDueNow(&time, &s_scheduledEvents[i]);
}

int LightScheduler_randomize(int id, DAY day, int minuteOfDay)
{
	for (int i = 0; i < MAX_EVENT_NUM; i++) {
		if (s_scheduledEvents[i].id == id
		 && s_scheduledEvents[i].day == day
		 && s_scheduledEvents[i].minuteOfDay == minuteOfDay) {
			s_scheduledEvents[i].minuteOfDay += RandomMinute_get();
			return LS_OK;
		}
	}
	return LS_ITEM_NOT_FOUND;
}
